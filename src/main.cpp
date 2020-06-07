#include "ncurses_display.h"
#include "system.h"
#include "format.h"

#include <iostream>
#include "linux_parser.h"
int main() {
    System system;
// system.Processes();
// for (auto &&process : system.Processes())
// {
//     std::cout << "Pid: " << process.Pid() << ", cpu: " << process.CpuUtilization() << std::endl; 
// }

    // std::cout << system.TotalProcesses() << std::endl;

    NCursesDisplay::Display(system);

    // Process process1(15057);
    // std:: cout << Format::ElapsedTime(process->UpTime()) << std::endl;
    // std:: cout << process->UpTime() << std::endl;
    // std:: cout << process->Ram() << std::endl;
    // std:: cout << process1.CpuUtilization() << std::endl;
    // std:: cout << process->Command() << std::endl;


    // Process process2(4895);
    // std:: cout << Format::ElapsedTime(process->UpTime()) << std::endl;
    // std:: cout << process->UpTime() << std::endl;
    // std:: cout << process->Ram() << std::endl;
    // std:: cout << process2.CpuUtilization() << std::endl;
    // std:: cout << process->Command() << std::endl;
    // std::vector<Process> processess = {process1, process2};
    // std::sort(processess.begin(), processess.end());

    // for (auto &&process : processess)
    // {
    //     std::cout << "Cpu: " << process.CpuUtilization() << std::endl;
    // }
    
}