#include "ExecutiveSelector.h"
#include "ToolApplication.h"

#include <dirent.h>
#include <fstream>

using namespace indra_toolkit;

// Executive Proc
std::vector<int> indra_toolkit::ExecutiveSelector::GetRunningExecutives()
{
    std::vector<int> running_executives;

#if defined(unix) || defined(__unix__) || defined(__unix)
    std::vector<st_proc_info> executives_proc = ReadRunningExecutivesProc();
    for (size_t i = 0; i < executives_proc.size(); i++)
    {
        running_executives.push_back(executives_proc[i].pid); 
    }
#endif

    return running_executives;
}

#if defined(unix) || defined(__unix__) || defined(__unix)

std::vector<st_proc_info> indra_toolkit::ExecutiveSelector::ReadRunningExecutivesProc()
{
    const std::string PATH = "/proc";

    std::vector<st_proc_info> executives_proc;

    DIR *dir = opendir(PATH.c_str());

    struct dirent *entry = readdir(dir);

    while (entry != NULL)
    {
        entry = readdir(dir);

        if (!entry)
            break;

        if (entry->d_type != DT_DIR)
            continue;

        std::string directory_name = entry->d_name;
        if (directory_name.find_first_not_of("0123456789") == std::string::npos)
        {
            st_proc_info proc_info = ReadProcInfo(PATH + "/" + directory_name + "/stat");
            if (proc_info.comm == "(executive)")
            {
                executives_proc.push_back(proc_info);
            }
        }
    }

    closedir(dir);

    return executives_proc;
}

st_proc_info indra_toolkit::ExecutiveSelector::ReadProcInfo(std::string path)
{
    st_proc_info proc_info;

    std::ifstream in(path);

    in  >> proc_info.pid
        >> proc_info.comm
        >> proc_info.state
        >> proc_info.ppid
        >> proc_info.pgrp
        >> proc_info.session
        >> proc_info.tty_nr
        >> proc_info.tpgid
        >> proc_info.flags
        >> proc_info.minflt
        >> proc_info.cminflt
        >> proc_info.majflt
        >> proc_info.cmajflt
        >> proc_info.utime
        >> proc_info.stime
        >> proc_info.cutime
        >> proc_info.cstime
        >> proc_info.priority
        >> proc_info.nice
        >> proc_info.num_threads
        >> proc_info.itrealvalue
        >> proc_info.startime
        >> proc_info.vsize
        >> proc_info.rss
        >> proc_info.rsslim
        >> proc_info.startcode
        >> proc_info.endcode
        >> proc_info.startstack
        >> proc_info.kstkesp
        >> proc_info.kstkeip
        >> proc_info.signal
        >> proc_info.blocked
        >> proc_info.sigignore
        >> proc_info.sigcatch
        >> proc_info.wchan
        >> proc_info.nswap
        >> proc_info.cnswap
        >> proc_info.exit_signal
        >> proc_info.processor
        >> proc_info.rt_priority
        >> proc_info.policy
        >> proc_info.delayacct_blkio_ticks
        >> proc_info.guest_time
        >> proc_info.cguest_time;

    return proc_info;
}
#endif