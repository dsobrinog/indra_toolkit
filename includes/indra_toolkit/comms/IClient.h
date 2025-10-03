#pragma once

#include "indra_toolkit/comms/comms_def.h"

namespace indra_toolkit
{
    class ToolApplication;

    /// @brief Abstraction used for separating comms libs (RPC, ZeroMQ...) from tools logic. 
    class IClient
    {
    public:
        IClient(NetworkConfiguration config): config_(config){};
        ~IClient() = default;

        virtual bool Connect() = 0;
        virtual void Disconnect() = 0;

        /// @brief RPC that request a value from remote server
        /// @param arg1 identifier or name of the value
        /// @return char pointer to the value
        virtual std::string Read(const char* arg1) = 0;

        /// @brief RPC that sends a value to remote server
        /// @param arg1 value
        /// @param arg2 address
        virtual void Write(char* arg1, const char* arg2) = 0;

        virtual void* ListMonitorSubstringBegin(int tool_pid, char* element) = 0;
        virtual bool ListMonitorSubstringEnd(int tool_pid) = 0; 
        virtual std::string ListMonitorSubstringGet(int tool_pid) = 0;
        virtual void* MonitorClose(int tool_pid) = 0;
        virtual int* Consult(std::string var_to_search) = 0;

        virtual void InitTimeExecutive() = 0;
        virtual void InitTimeModules() = 0;
        virtual std::string GetModuleName(int index) = 0;

    protected:
        NetworkConfiguration config_;
};
}
