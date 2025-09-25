#include "RpcClient.h"
#include <iostream>

#include "comms/RPCGEN/HxComServ.h"


using namespace indra_toolkit;

RpcClient::RpcClient(const NetworkConfiguration& config)
    : IClient(config)
{
}

RpcClient::~RpcClient()
{
    Disconnect();
}

bool RpcClient::Connect()
{
    clnt = clnt_create(
        config_.ip.c_str(),
        static_cast<rpcprog_t>(config_.programNumber),
        static_cast<rpcvers_t>(config_.versionNumber),
        config_.protocol.c_str()
    );

    if (clnt == nullptr)
    {
        clnt_pcreateerror(config_.ip.c_str()); // prints RPC-specific error
        std::cerr << "\n\n @Failed get_rpcVersion("
                    << config_.ip << ", "
                    << std::hex << config_.programNumber << ", "
                    << config_.versionNumber << ", "
                    << config_.protocol << ")"
                    << std::endl;
        return false; 
    }
    else
    {
        std::cout << "\n **** Created Simulation Virtual Console (" << config_.name_app << ") version "
                    << config_.versionNumber << " (Executive Num: " << config_.versionNumber 
                    << ") in server " << config_.ip
                    << " ****" << std::endl;

        std::cout << ">>> Tool data: " << config_.name_app << ", pid: " << getpid()
                    << ", thread id: " << pthread_self()
                    << std::endl;

        return true;
    }
}

void RpcClient::Disconnect()
{
    if (clnt)
    {
        clnt_destroy(clnt);
        clnt = nullptr;
    }
}

std::string indra_toolkit::RpcClient::Read(const char* arg1)
{
    if (!clnt) return nullptr;
    char **res = leo_1(arg1, clnt);
    if (!res || !*res) return std::string("");
    return std::string(*res);
}

void indra_toolkit::RpcClient::Write(char* arg1, const char* arg2)
{
    escribo_1(arg1, arg2, clnt);
}

void* indra_toolkit::RpcClient::ListMonitorSubstringBegin(int tool_pid, char* element)
{
    return lista_monitor_substring_begin__1(tool_pid, element, clnt);
}

bool indra_toolkit::RpcClient::ListMonitorSubstringEnd(int tool_pid)
{
    return *(bool*)lista_monitor_substring_end__1(tool_pid, clnt); 
}

std::string indra_toolkit::RpcClient::ListMonitorSubstringGet(int tool_pid) 
{
    char** auxCad = lista_monitor_substring_get__1(tool_pid, clnt); 
    if(!auxCad) return std::string();
    
    return std::string(*auxCad);
}

void* indra_toolkit::RpcClient::MonitorClose(int tool_pid)
{
    return monitor_close_1(tool_pid, clnt); 
}void indra_toolkit::RpcClient::InitTimeExecutive()
{
    inittiempoejecutivo_1(clnt);
}

void indra_toolkit::RpcClient::InitTimeModules()
{
    inittiempomodulos_1(clnt);
}

std::string indra_toolkit::RpcClient::GetModuleName(int index)
{
    if (!clnt) return nullptr; // No client
    char **res = getmodulename_1(index, clnt);
    if (!res || !*res) return nullptr; // No result
    return std::string(*res);
}
