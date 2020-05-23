#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <map>

#include "process_stat.h"
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
   public:
    Process(int pid);
    int Pid();                               // TODO: See src/process.cpp
    std::string User();                      // TODO: See src/process.cpp
    std::string Command();                   // TODO: See src/process.cpp
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    bool operator<(Process const& a) const;  // TODO: See src/process.cpp

   private:
    int pid;
    ProcessStat process_stat;
    float cpu;
    std::map<std::string, std::string> ParseStatFileAsKeyAndOnlyOneValue(std::string path);
};

#endif