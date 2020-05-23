#ifndef PROCESS_STAT_H
#define PROCESS_STAT_H

#include <string>
#include <iostream>

class ProcessStat {
   public:
    ProcessStat(std::string path);
    friend std::ostream& operator<< (std::ostream& out, const ProcessStat& obj); 

    int pid;
    std::string comm;
    char state;
    int ppid;
    int pgrp;
    int session;
    int tty_nr;
    int tpgid;
    uint flags;
    unsigned long int minflt;
    unsigned long int cminflt;
    unsigned long int majflt;
    unsigned long int cmajflt;
    unsigned long int utime;
    unsigned long int stime;
    unsigned long int cutime;
    long int cstime;
    long int priority;
    long int nice;
    long int num_threads;
    long int itrealvalue;
    long unsigned long int starttime;
    unsigned long int vsize;
    long int rss;
    unsigned long int rsslim;
    unsigned long int startcode;
    unsigned long int endcode;
    unsigned long int startstack;
    unsigned long int kstkesp;
    unsigned long int kstkeip;
    unsigned long int signal;
    unsigned long int blocked;
    unsigned long int sigignore;
    unsigned long int sigcatch;
    unsigned long int wchan;
    unsigned long int nswap;
    unsigned long int cnswap;
    int exit_signal;
    int processor;
    uint rt_priority;
    uint policy;
    long unsigned long int delayacct_blkio_ticks;
    unsigned long int guest_time;
    long int cguest_time;
    unsigned long int start_data;
    unsigned long int end_data;
    unsigned long int start_brk;
    unsigned long int arg_start;
    unsigned long int arg_end;
    unsigned long int env_start;
    unsigned long int env_end;
    int exit_code;
};

#endif