#include <dirent.h>
#include <unistd.h>
#include <filesystem>  // g++ 8 in Ubuntu
#include <string>
#include <vector>

#include "linux_parser.h"

#include <iostream>
    
char const* DIGITS = "0123456789";

// Inner and annonymous namespace. Just wanted to use a map for obtaining the
// Operating System. This map could easily be saved globally and just parse it
// once if more data of /etc/os-release is needed.
namespace {
std::map<std::string, std::string> CreateMapFromFileAndDivisor(std::string file,
                                                               char divisor) {
    std::string line;
    std::string key;
    std::string value;
    std::map<std::string, std::string> result{};
    std::ifstream filestream(file);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
            const std::size_t index = line.find_first_of(divisor);
            if (index == std::string::npos) {
                continue;
            }
            key = line.substr(0, index);
            value = line.substr(index + 1, line.length());
            result[key] = value;
        }
    }
    return result;
}

int ParseStatFileForProcesses(std::string key) {
    std::string line;
    std::string processes;
    int totalProcesses;
    std::ifstream filestream(LinuxParser::kProcDirectory +
                             LinuxParser::kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            // Original code that reads all lines and contents of a line.
            // while(linestream >> processes >> totalProcesses) {
            //     if (processes == "processes") {
            //         return totalProcesses;
            //     }
            // }
            while (linestream >> processes) {
                if (processes == key) {
                    linestream >> totalProcesses;
                    return totalProcesses;
                } else {
                    break;  // This line is not the desired one, so continue to
                            // next line instead of reading the rest of the
                            // line. I prefer this way,
                }
            }
        }
    }
    return totalProcesses;
}
}  // namespace

std::string LinuxParser::OperatingSystem() {
    return ::CreateMapFromFileAndDivisor(kOSPath, '=')["PRETTY_NAME"];
}

std::string LinuxParser::Kernel() {
    std::string os, kernel, version;
    std::string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
}

std::vector<int> LinuxParser::Pids() {
    std::vector<int> pids{};
    for (const auto& directory :
        std::filesystem::directory_iterator(kProcDirectory)) {
        std::string filename = directory.path().filename();
        if (std::all_of(filename.begin(), filename.end(), isdigit)) {
            const int pid = stoi(filename);
            pids.push_back(pid);
        }
    }
    return pids;
}

float LinuxParser::MemoryUtilization() {
    auto memory =
        ::CreateMapFromFileAndDivisor(kProcDirectory + kMeminfoFilename, ':');
    std::string totalString = memory["MemTotal"];
    totalString.erase(std::remove(totalString.begin(), totalString.end(), ' '),
                      totalString.end());
    const float total = atof(totalString.c_str());

    std::string freeString = memory["MemFree"];
    freeString.erase(std::remove(freeString.begin(), freeString.end(), ' '),
                     freeString.end());
    const float free = atof(freeString.c_str());

    return (total - free) / total;
}

float LinuxParser::UpTime() {
    std::string uptime, idle;
    std::string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> uptime >> idle;
    }
    return atof(uptime.c_str());
}

std::vector<std::string> LinuxParser::CpuUtilization() {
    std::string line;
    std::ifstream stream(kProcDirectory + kStatFilename);
    getline(stream, line);  // Only cpu0 is needed.

    std::string cpu, user, nice, system, idle, iowait, irq, softirq, steal,
        guest, guest_nice;
    std::stringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >>
        softirq >> steal >> guest >> guest_nice;

    return {user, nice,    system, idle,  iowait,
            irq,  softirq, steal,  guest, guest_nice};
}

int LinuxParser::TotalProcesses() {
    return ::ParseStatFileForProcesses("processes");
}

int LinuxParser::RunningProcesses() {
    return ::ParseStatFileForProcesses("procs_running");
}

std::string LinuxParser::Command(int pid) {
    std::ifstream cmd_stream(kProcDirectory + std::to_string(pid) + "/" + kCmdlineFilename);
    std::string line;
    if (cmd_stream.is_open()) {
        std::getline(cmd_stream, line);
    }
    return line;
}

std::string LinuxParser::Ram(int pid) {
    std::string ram = ::CreateMapFromFileAndDivisor(kProcDirectory + std::to_string(pid) + "/" + kStatusFilename, ':')["VmSize"];
    std::size_t index = ram.find_first_of(DIGITS);
    ram = ram.substr(index, ram.size());
    index = ram.find_first_not_of(DIGITS);
    const float kilobytes = atof(ram.substr(0, index).c_str());
    const float megabytes = kilobytes / 1000;
    
    std::stringstream ss;
    ss << std::fixed;
    ss.precision(2); // set # places after decimal
    ss << megabytes;
    return ss.str();
}

std::string LinuxParser::Uid(int pid) {
    const std::string user = User(pid);

    std::string divisor = ":";
    std::string line;
    std::ifstream stream("/etc/passwd");
    if (stream.is_open()) {
        while (getline(stream, line)) {
            std::string name, variable, user_pid;
            std::size_t index = line.find_first_of(divisor);
            name = line.substr(0, index);
            line = line.substr(index + 1, line.size());

            index = line.find_first_of(divisor);
            variable = line.substr(0, index);
            line = line.substr(index + 1, line.size());

            index = line.find_first_of(divisor);
            user_pid = line.substr(0, index);
            line = line.substr(index + 1, line.size());

            if (user_pid.compare(user) == 0) {
                return name;
            }
        }
    }
    return "NO USER";
}

std::string LinuxParser::User(int pid) {
    std::string long_user = ::CreateMapFromFileAndDivisor(kProcDirectory + std::to_string(pid) + "/" + kStatusFilename, ':')["Uid"];
    const std::size_t start = long_user.find_first_of(DIGITS);
    const std::size_t end = long_user.find_first_not_of(DIGITS, start);
    const std::string int_user = long_user.substr(start, end != std::string::npos ? end-start : end);
    return int_user;
}
