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
    int Pid() const;
    std::string User() const;
    std::string Command() const;
    float CpuUtilization();
    std::string Ram() const;
    long int UpTime() const;
    bool operator<(Process const& a) const;

   private:
    int pid;
    float cpu = -1;
    ProcessStat process_stat;
    std::map<std::string, std::string> ParseStatFileAsKeyAndOnlyOneValue(std::string path);
};

#endif