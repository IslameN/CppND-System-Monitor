#include "ncurses_display.h"
#include "system.h"
#include "format.h"

#include <iostream>
#include "linux_parser.h"
int main() {
    System system;

    // std::cout << system.TotalProcesses() << std::endl;

    NCursesDisplay::Display(system);

    // Process* process = new Process(1);
    // std:: cout << Format::ElapsedTime(process->UpTime()) << std::endl;
    // std:: cout << process->UpTime() << std::endl;
    // std:: cout << process->Ram() << std::endl;
    // std:: cout << process->CpuUtilization() << std::endl;
    // std:: cout << process->Command() << std::endl;
    // std:: cout << process->User() << std::endl;
    // std:: cout << LinuxParser::User(16) << std::endl;


    // process = new Process(10166);
    // std:: cout << process->UpTime() << std::endl;
    // std:: cout << process->Ram() << std::endl;
    // std:: cout << process->CpuUtilization() << std::endl;
    // std:: cout << process->Command() << std::endl;
}