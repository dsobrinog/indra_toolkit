#pragma once

#include "indra_toolkit/comms/IClient.h"
#include <rpc/rpc.h> // forward declare CLIENT type

namespace indra_toolkit
{
    class RpcClient : public IClient
    {
    public:
        RpcClient(const NetworkConfiguration& config);
        ~RpcClient();

        bool Connect() override;
        void Disconnect() override;

        std::string Read(const char* arg1);
        void Write(char* arg1, const char* arg2);

        void InitTimeExecutive();
        void InitTimeModules();
        std::string GetModuleName(int index);

        void* ListMonitorSubstringBegin(int tool_pid, char* element) override;
        bool ListMonitorSubstringEnd(int tool_pid) override; 
        std::string ListMonitorSubstringGet(int tool_pid) override;
        virtual void* MonitorClose(int tool_pid) override;
        virtual int* Consult(std::string var_to_search) override;

    private:
        CLIENT* clnt = nullptr; // from Sun RPC
    };
}
