/*
 * Utilities and definitions related to OS level functions.
 */

#ifndef OS_MEMORY_UTILS_H
#define OS_MEMORY_UTILS_H

// STL
#include <ios>      // ios_base
#include <iostream> // cout, cerr, endl
#include <sstream>  // stringstream
#include <fstream>  // ifstream

// Linux Specific Functions
#include <sys/types.h> // uint32_t, uint64_t, etc
#include <sys/stat.h>  // stat (check a file exists)
#include <unistd.h>    // sysconf

namespace osmemory {


// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memoryUsed
// m_size and resident set m_size, and return the results in KB.
//
// On failure, returns 0.0, 0.0
//
// http://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-run-time-in-c
    inline
    void process_mem_usage(size_t &vm_usage, size_t &resident_set) {
        vm_usage = 0;
        resident_set = 0;

        // 'file' stat seems to give the most reliable results
        std::ifstream stat_stream("/proc/self/stat", std::ios_base::in);

        // dummy vars for leading entries in stat that we don't care about
        std::string pid, comm, state, ppid, pgrp, session, tty_nr;
        std::string tpgid, flags, minflt, cminflt, majflt, cmajflt;
        std::string utime, stime, cutime, cstime, priority, nice;
        std::string O, itrealvalue, starttime;

        // the two fields we want
        size_t vsize;
        size_t rss;

        stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
                    >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt >> utime
                    >> stime >> cutime >> cstime >> priority >> nice >> O >> itrealvalue
                    >> starttime >> vsize >> rss; // don't care about the rest
        stat_stream.close();

        size_t page_size = (size_t) sysconf(_SC_PAGE_SIZE); // in case x86-64 is configured to use 2MB pages
        vm_usage = vsize;
        resident_set = rss * page_size;
    }

    // Get the all the RAM available to the OS.
    //
    // Returns RAM in bytes
    inline
    size_t get_total_system_memory() {
        long pages = sysconf(_SC_PHYS_PAGES);
        long page_size = sysconf(_SC_PAGE_SIZE);
        return (size_t) (pages * page_size);
    }

}

#endif // OS_MEMORY_UTILS_H

