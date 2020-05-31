#include <unistd.h>
#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

Processor& System::Cpu() { return cpu_; }

std::vector<Process>& System::Processes() {
    if (processes.size() != 0) {
        processes.clear();
    }
    for (int pid : LinuxParser::Pids()) {
        Process process(pid);
        if (!process.Command().empty()) {
            processes.push_back(process);
        }
    }
    std::sort(processes.begin(), processes.end());
    return processes;
}

std::string System::Kernel() { return LinuxParser::Kernel(); }

float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long int System::UpTime() { return LinuxParser::UpTime(); }