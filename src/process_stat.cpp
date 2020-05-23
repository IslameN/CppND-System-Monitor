#include "process_stat.h"
#include <fstream>
#include <sstream>

ProcessStat::ProcessStat(std::string path) {
    std::ifstream file_stream(path);
    std::string line;
    if (file_stream.is_open()) {
        std::getline(file_stream, line);
        std::istringstream stream(line);
        stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
        >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt 
        >> utime >> stime >> cutime >> cstime >> priority >> nice 
        >> num_threads >> itrealvalue >> starttime >> vsize >> rss 
        >> rsslim >> startcode >> endcode >> startstack >> kstkesp 
        >> kstkeip >> signal >> blocked >> sigignore >> sigcatch 
        >> wchan >> nswap >> cnswap >> exit_signal >> processor 
        >> rt_priority >> policy >> delayacct_blkio_ticks >> guest_time 
        >> cguest_time >> start_data >> end_data >> start_brk >> arg_start 
        >> arg_end >> env_start >> env_end >> exit_code;
    }
}

std::ostream& operator<< (std::ostream &out, ProcessStat const& process_stat) {
    out << process_stat.pid << " ";
    out << process_stat.comm << " ";
    out << process_stat.state << " ";
    out << process_stat.ppid << " ";
    out << process_stat.pgrp << " ";
    out << process_stat.session << " ";
    out << process_stat.tty_nr << " ";
    out << process_stat.tpgid << " ";
    out << process_stat.flags << " ";
    out << process_stat.minflt << " ";
    out << process_stat.cminflt << " ";
    out << process_stat.majflt << " ";
    out << process_stat.cmajflt << " ";
    out << process_stat.utime << " ";
    out << process_stat.stime << " ";
    out << process_stat.cutime << " ";
    out << process_stat.cstime << " ";
    out << process_stat.priority << " ";
    out << process_stat.nice << " ";
    out << process_stat.num_threads << " ";
    out << process_stat.itrealvalue << " ";
    out << process_stat.starttime << " ";
    out << process_stat.vsize << " ";
    out << process_stat.rss << " ";
    out << process_stat.rsslim << " ";
    out << process_stat.startcode << " ";
    out << process_stat.endcode << " ";
    out << process_stat.startstack << " ";
    out << process_stat.kstkesp << " ";
    out << process_stat.kstkeip << " ";
    out << process_stat.signal << " ";
    out << process_stat.blocked << " ";
    out << process_stat.sigignore << " ";
    out << process_stat.sigcatch << " ";
    out << process_stat.wchan << " ";
    out << process_stat.nswap << " ";
    out << process_stat.cnswap << " ";
    out << process_stat.exit_signal << " ";
    out << process_stat.processor << " ";
    out << process_stat.rt_priority << " ";
    out << process_stat.policy << " ";
    out << process_stat.delayacct_blkio_ticks << " ";
    out << process_stat.guest_time << " ";
    out << process_stat.cguest_time << " ";
    out << process_stat.start_data << " ";
    out << process_stat.end_data << " ";
    out << process_stat.start_brk << " ";
    out << process_stat.arg_start << " ";
    out << process_stat.arg_end << " ";
    out << process_stat.env_start << " ";
    out << process_stat.env_end << " ";
    out << process_stat.exit_code;
    return out;
}