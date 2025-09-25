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


    private:
        CLIENT* clnt = nullptr; // from Sun RPC
    };
}
