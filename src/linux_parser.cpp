#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem> // g++ 8 in Ubuntu

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// Inner and annonymous namespace. Just wanted to use a map for obtaining the Operating
// System. This map could easily be saved globally and just parse it once if more data of 
// /etc/os-release is needed.
namespace {
    std::map<std::string, std::string> OperatingSystemMap() {
        string line;
        string key;
        string value;
        std::map<std::string, std::string> result {};
        std::ifstream filestream(LinuxParser::kOSPath);
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                line.erase(std::remove(line.begin(), line.end(), '"'), line.end());
                std::size_t index = line.find_first_of("=");
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
}

string LinuxParser::OperatingSystem() {
    return ::OperatingSystemMap()["PRETTY_NAME"];
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
    string os, kernel;
    string line;
    std::ifstream stream(kProcDirectory + kVersionFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        linestream >> os >> kernel;
    }
    return kernel;
}

vector<int> LinuxParser::Pids() {
    vector<int> pids {};
    for (const auto& directory : std::filesystem::directory_iterator(kProcDirectory)) {
        std::string filename = directory.path().filename();
        if (std::all_of(filename.begin(), filename.end(), isdigit)) {
            int pid = stoi(filename);
            pids.push_back(pid);
        }
    }
    return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { return 0.0; }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { return 0; }

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }
