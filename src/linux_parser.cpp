#include <dirent.h>
#include <unistd.h>
#include <filesystem>  // g++ 8 in Ubuntu
#include <string>
#include <vector>

#include "linux_parser.h"

#include <iostream>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Inner and annonymous namespace. Just wanted to use a map for obtaining the
// Operating System. This map could easily be saved globally and just parse it
// once if more data of /etc/os-release is needed.
namespace {
std::map<std::string, std::string> CreateMapFromFileAndDivisor(std::string file,
                                                               char divisor) {
    string line;
    string key;
    string value;
    std::map<std::string, std::string> result{};
    std::ifstream filestream(file);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
            std::size_t index = line.find_first_of(divisor);
            if (index == string::npos) {
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
    string line;
    string processes;
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

string LinuxParser::OperatingSystem() {
    return ::CreateMapFromFileAndDivisor(kOSPath, '=')["PRETTY_NAME"];
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
    string os, kernel, version;
    string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> version >> kernel;
    }
    return kernel;
}

vector<int> LinuxParser::Pids() {
    vector<int> pids{};
    for (const auto& directory :
        std::filesystem::directory_iterator(kProcDirectory)) {
        std::string filename = directory.path().filename();
        if (std::all_of(filename.begin(), filename.end(), isdigit)) {
            int pid = stoi(filename);
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
    float total = atof(totalString.c_str());

    std::string freeString = memory["MemFree"];
    freeString.erase(std::remove(freeString.begin(), freeString.end(), ' '),
                     freeString.end());
    float free = atof(freeString.c_str());

    return (total - free) / total;
}

long LinuxParser::UpTime() {
    string uptime, idle;
    string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> uptime >> idle;
    }
    return atol(uptime.c_str());
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

vector<string> LinuxParser::CpuUtilization() {
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

string LinuxParser::Command(int pid) {
    std::ifstream cmd_stream(kProcDirectory + std::to_string(pid) + "/" + kCmdlineFilename);
    std::string line;
    if (cmd_stream.is_open()) {
        std::getline(cmd_stream, line);
    }
    return line;
}

string LinuxParser::Ram(int pid) {
    return ::CreateMapFromFileAndDivisor(kProcDirectory + std::to_string(pid) + "/" + kStatusFilename, ':')["VmSize"];
    // return ParseStatFileAsKeyAndOnlyOneValue(path)["VmSize"];
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

string LinuxParser::User(int pid) {
    std::string long_user = ::CreateMapFromFileAndDivisor(kProcDirectory + std::to_string(pid) + "/" + kStatusFilename, ':')["Uid"];
    char const* digits = "0123456789";
    std::size_t const start = long_user.find_first_of(digits);
    std::size_t const end = long_user.find_first_not_of(digits, start);
    std::string int_user = long_user.substr(start, end != std::string::npos ? end-start : end);
    return int_user;
}
