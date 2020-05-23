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

Process::Process(int pid) : pid(pid), process_stat(LinuxParser::kProcDirectory + std::to_string(pid) + "/stat") {
    std::cout << "Process" << std::endl;
    std::cout << process_stat << std::endl;
}

int Process::Pid() {
    return pid;
}

float Process::CpuUtilization() {
    float total_time = process_stat.utime + process_stat.stime + process_stat.cutime + process_stat.cstime;
    unsigned long int seconds = LinuxParser::UpTime() - (process_stat.starttime / HERTZ);

    cpu = (total_time / HERTZ) / seconds;
    return cpu;
}

string Process::Command() {
    return LinuxParser::Command(pid);
}

string Process::Ram() {
    return LinuxParser::Ram(pid);
}

string Process::User() {
    return LinuxParser::User(pid);
}

long int Process::UpTime() {
    return process_stat.utime / HERTZ;
}

bool Process::operator<(Process const& other) const {
    return (pid > other.pid);
}