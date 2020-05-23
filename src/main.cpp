#include "ncurses_display.h"
#include "system.h"
#include "format.h"

#include <iostream>

int main() {
    System system;
    // NCursesDisplay::Display(system);
    Process* process = new Process(11075);
    std:: cout << Format::ElapsedTime(process->UpTime()) << std::endl;
    std:: cout << process->UpTime() << std::endl;
    std:: cout << process->Ram() << std::endl;
    std:: cout << process->CpuUtilization() << std::endl;
    std:: cout << process->Command() << std::endl;
    std:: cout << process->User() << std::endl;


    // process = new Process(10166);
    // std:: cout << process->UpTime() << std::endl;
    // std:: cout << process->Ram() << std::endl;
    // std:: cout << process->CpuUtilization() << std::endl;
    // std:: cout << process->Command() << std::endl;
    // system.TotalProcesses();
    // system.Processes();
}