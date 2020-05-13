#include "processor.h"

#include "linux_parser.h"

#include <iostream>

float Processor::Utilization() {
    std::vector<std::string> cpu_values = LinuxParser::CpuUtilization();

    int current_user = atoi(cpu_values[0].c_str());
    int current_nice = atoi(cpu_values[1].c_str());
    int current_system = atoi(cpu_values[2].c_str());
    int current_idle = atoi(cpu_values[3].c_str());
    int current_iowait = atoi(cpu_values[4].c_str());
    int current_irq = atoi(cpu_values[5].c_str());
    int current_softirq = atoi(cpu_values[6].c_str());
    int current_steal = atoi(cpu_values[7].c_str());
    int current_guest = atoi(cpu_values[8].c_str());
    int current_guest_nice = atoi(cpu_values[9].c_str());
    
    int prev_idle = idle + iowait;
    int new_idle = current_idle + current_iowait;
    int prev_non_idle = user + nice + system + irq + softirq + steal;
    int non_idle = current_user + current_nice + current_system + current_irq + current_softirq + current_steal;
    int prev_total = prev_idle + prev_non_idle;
    int total = new_idle + non_idle;
    int total_diff = total - prev_total;
    int idle_diff = new_idle - prev_idle;

    user = current_user;
    nice = current_nice;
    system = current_system;
    idle = current_idle;
    iowait = current_iowait;
    irq = current_irq;
    softirq = current_softirq;
    steal = current_steal;
    guest = current_guest;
    guest_nice = current_guest_nice;

    return (float)(total_diff - idle_diff) / total_diff;
}