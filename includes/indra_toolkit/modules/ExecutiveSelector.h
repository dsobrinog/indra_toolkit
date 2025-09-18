#pragma once

#include "indra_toolkit/Module.h"
#include "indra_toolkit/layers/InteractiveLayer.h"

#include <vector>
#include <functional>

namespace indra_toolkit
{
    class ComboBoxWidget;
}

namespace indra_toolkit
{
    struct st_proc_info;


    /// @brief Get PIDs of running executives in the same machine
    class ExecutiveSelector : public Module
    {
    public:
        ExecutiveSelector(ToolApplication* app_, const ToolModules& moduleIdentity_) : Module(app_, moduleIdentity_){}

        virtual bool OnInit() override;

        virtual void OnShutdown() override;

        virtual bool IsDeferred() const { return false; }

        /// @brief Retrieve a list with the PIDs of the current running Executives in this machine
        /// @return list of executive running PIDs
        std::vector<int> GetRunningExecutives();

        void SetOnExecutiveSelectedCallback(std::function<void(int)> callback_) { on_exec_selected = callback_; }
        void SetSelectorWindowName(const std::string& in_name_of_window_) { name_of_selector_window = in_name_of_window_;}

    private:

        void CreateExecutiveComboBox(const std::vector<int>& runningExecutivesIDs); 

        void OnConfirmButtonPressed();

        #if defined(unix) || defined(__unix__) || defined(__unix)

        std::vector<st_proc_info> ReadRunningExecutivesProc();
        st_proc_info ReadProcInfo(std::string path);

        #endif

        InteractiveLayer* interactive_layer = nullptr;
        ComboBoxWidget* combo_box = nullptr;

        ImVec2 original_wnd_size;

        std::function<void(int)> on_exec_selected;
        std::string name_of_selector_window;
    };

     // Process linux data
    struct st_proc_info
    {
        // The process ID.
        int pid;

        // The filename of the executable, in parentheses. This is visible whether
        // or not the executable is swapped out.
        std::string comm;

        // One character from the string "RSDZTW" where R is running, S is sleeping
        // in an interruptible wait, D is waiting in uninterruptible disk sleep, Z
        // is zombie, T is traced or stopped (on a signal), and W is paging.
        char state;

        // The PID of the parent.
        int ppid;

        // The process group ID of the process.
        int pgrp;

        // The session ID of the process.
        int session;

        // The controlling terminal of the process. (The minor device number is
        // contained in the combination of bits 31 to 20 and 7 to 0; the major
        // device number is in bits 15 to 8.)
        int tty_nr;

        // The ID of the foreground process group of the controlling terminal of
        // the process.
        int tpgid;

        // The kernel flags word of the process. For bit meanings, see the PF_*
        // defines in the Linux kernel source file include/linux/sched.h. Details
        // depend on the kernel version.
        unsigned int flags;

        // The number of minor faults the process has made which have not required
        // loading a memory page from disk.
        unsigned long int minflt;

        // The number of minor faults that the process's waited-for children have
        // made.
        unsigned long int cminflt;

        // The number of major faults the process has made which have required
        // loading a memory page from disk.
        unsigned long int majflt;

        // The number of major faults that the process's waited-for children have
        // made.
        unsigned long int cmajflt;

        // Amount of time that this process has been scheduled in user mode,
        // measured in clock ticks (divide by sysconf(_SC_CLK_TCK)). This includes
        // guest time, guest_time (time spent running a virtual CPU, see below), so
        // that applications that are not aware of the guest time field do not lose
        // that time from their calculations.
        unsigned long int utime;

        // Amount of time that this process has been scheduled in kernel mode,
        // measured in clock ticks (divide by sysconf(_SC_CLK_TCK)).
        unsigned long int stime;

        // Amount of time that this process's waited-for children have been
        // scheduled in user mode, measured in clock ticks (divide by
        // sysconf(_SC_CLK_TCK)). (See also times(2).) This includes guest time,
        // cguest_time (time spent running a virtual CPU, see below).
        long int cutime;

        // Amount of time that this process's waited-for children have been
        // scheduled in kernel mode, measured in clock ticks (divide by
        // sysconf(_SC_CLK_TCK)). 
        long int cstime;

        // (Explanation for Linux 2.6) For processes running a real-time scheduling
        // policy (policy below; see sched_setscheduler(2)), this is the negated
        // scheduling priority, minus one; that is, a number in the range -2 to
        // -100, corresponding to real-time priorities 1 to 99. For processes
        // running under a non-real-time scheduling policy, this is the raw nice
        // value (setpriority(2)) as represented in the kernel. The kernel stores
        // nice values as numbers in the range 0 (high) to 39 (low), corresponding
        // to the user-visible nice range of -20 to 19. Before Linux 2.6, this was
        // a scaled value based on the scheduler weighting given to this process.
        long int priority;

        // The nice value (see setpriority(2)), a value in the range 19 (low
        // priority) to -20 (high priority).
        long int nice;

        // Number of threads in this process (since Linux 2.6). Before kernel 2.6,
        // this field was hard coded to 0 as a placeholder for an earlier removed
        // field.
        long int num_threads;

        // The time in jiffies before the next SIGALRM is sent to the process due
        // to an interval timer. Since kernel 2.6.17, this field is no longer
        // maintained, and is hard coded as 0.
        long int itrealvalue;

        // The time the process started after system boot. In kernels before Linux
        // 2.6, this value was expressed in jiffies. Since Linux 2.6, the value is
        // expressed in clock ticks (divide by sysconf(_SC_CLK_TCK)).
        unsigned long long startime;

        // Virtual memory size in bytes.
        unsigned long int vsize;

        // Resident Set Size: number of pages the process has in real memory. This
        // is just the pages which count toward text, data, or stack space. This
        // does not include pages which have not been demand-loaded in, or which
        // are swapped out.
        long int rss;

        // Current soft limit in bytes on the rss of the process; see the
        // description of RLIMIT_RSS in getrlimit(2).
        unsigned long int rsslim;

        // The address above which program text can run.
        unsigned long int startcode;

        // The address below which program text can run.
        unsigned long int endcode;

        // The address of the start (i.e., bottom) of the stack.
        unsigned long int startstack;

        // The current value of ESP (stack pointer), as found in the kernel stack
        // page for the process.
        unsigned long int kstkesp;

        // The current EIP (instruction pointer).
        unsigned long int kstkeip;

        // The bitmap of pending signals, displayed as a decimal number. Obsolete,
        // because it does not provide information on real-time signals; use
        // /proc/[pid]/status instead.
        unsigned long int signal;

        // The bitmap of blocked signals, displayed as a decimal number. Obsolete,
        // because it does not provide information on real-time signals; use
        // /proc/[pid]/status instead.
        unsigned long int blocked;

        // The bitmap of ignored signals, displayed as a decimal number. Obsolete,
        // because it does not provide information on real-time signals; use
        // /proc/[pid]/status instead. 
        unsigned long int sigignore;

        // The bitmap of caught signals, displayed as a decimal number. Obsolete,
        // because it does not provide information on real-time signals; use
        // /proc/[pid]/status instead. 
        unsigned long int sigcatch;

        // This is the "channel" in which the process is waiting. It is the address
        // of a system call, and can be looked up in a namelist if you need a
        // textual name. (If you have an up-to-date /etc/psdatabase, then try ps -l
        // to see the WCHAN field in action.)
        unsigned long int wchan;

        // Number of pages swapped (not maintained).
        unsigned long int nswap;

        // Cumulative nswap for child processes (not maintained).
        unsigned long int cnswap;

        // Signal to be sent to parent when we die.
        int exit_signal;

        // CPU number last executed on.
        int processor;

        // Real-time scheduling priority, a number in the range 1 to 99 for
        // processes scheduled under a real-time policy, or 0, for non-real-time
        // processes (see sched_setscheduler(2)).
        unsigned int rt_priority;

        // Scheduling policy (see sched_setscheduler(2)). Decode using the SCHED_*
        // constants in linux/sched.h.
        unsigned int policy;

        // Aggregated block I/O delays, measured in clock ticks (centiseconds).
        unsigned long long delayacct_blkio_ticks;

        // Guest time of the process (time spent running a virtual CPU for a guest
        // operating system), measured in clock ticks (divide by
        // sysconf(_SC_CLK_TCK)).
        unsigned long int guest_time;

        // Guest time of the process's children, measured in clock ticks (divide
        // by sysconf(_SC_CLK_TCK)).
        long int cguest_time;
    };
}
