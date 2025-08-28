#pragma once

#include "comms/IClient.h"
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

        char* Read(const char* arg1);
        void Write(char* arg1, const char* arg2);

    private:
        CLIENT* clnt = nullptr; // from Sun RPC
    };
}
