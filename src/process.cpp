#include <unistd.h>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>

#include "linux_parser.h"

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

const auto HERTZ = sysconf(_SC_CLK_TCK);

Process::Process(int pid) : pid(pid), process_stat(LinuxParser::kProcDirectory + std::to_string(pid) + "/" + LinuxParser::kStatFilename) {
    cpu = CpuUtilization();
    // TODO: maybe all Process calls can be stored as properties and set in this constructor
}

int Process::Pid() const {
    return pid;
}

float Process::CpuUtilization() {
    if (cpu == -1) {
        float total_time = process_stat.utime + process_stat.stime + process_stat.cutime + process_stat.cstime;
        float seconds = (float)LinuxParser::UpTime() - (process_stat.starttime / HERTZ);;
        cpu = (total_time / HERTZ) / seconds;
        if (cpu > 1) {
            cpu = 1;
        } else if (cpu < 0) {
            cpu = 0;
        }
    }
    return cpu;
}

string Process::Command() const {
    return LinuxParser::Command(pid);
}

string Process::Ram() const {
    return LinuxParser::Ram(pid);
}

string Process::User() const {
    return LinuxParser::Uid(pid);
}

long int Process::UpTime() const {
    return process_stat.utime / HERTZ;
}

bool Process::operator < (const Process& other) const {
    return (other.cpu < cpu);
}