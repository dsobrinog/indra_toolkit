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
        virtual char* Read(const char* arg1) = 0;

        /// @brief RPC that sends a value to remote server
        /// @param arg1 value
        /// @param arg2 address
        virtual void Write(char* arg1, const char* arg2) = 0;

     protected:
        NetworkConfiguration config_;
};
}
