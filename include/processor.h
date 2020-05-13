#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>

class Processor {
   public:
    float Utilization();

   private:
    int user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
};

#endif