#pragma once

#include <string>

enum COMMS_LIB
{
    RPC,
    ZMQ
};

struct NetworkConfiguration
{
    std::string ip = "127.0.0.1";
    std::string port = "5556";

    std::string name_app = "inexconsole";

    // RPC-specific
    uint32_t programNumber = 0x50000001;   // rpcprog_t
    uint32_t versionNumber = 1;   // rpcvers_t
    std::string protocol   = "udp"; // "udp" or "tcp"
    COMMS_LIB lib = RPC;
};