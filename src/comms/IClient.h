#pragma once

#include "comms/comms_def.h"

namespace indra_toolkit
{
    class ToolApplication;

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
        /// @param arg1 
        /// @param arg2 
        virtual void Write(char* arg1, const char* arg2) = 0;

     protected:
        NetworkConfiguration config_;
};
}
