#pragma once

#include "indra_toolkit/Module.h"

#include <unordered_map>
#include <queue>
#include <mutex>
#include <iostream>

namespace indra_toolkit
{

/// @brief Register commands at start, push commands runtime from main thread and secondary thread will consume them
/// @tparam CommandEnum custom command enum
template<typename CommandEnum>
class CommandCallback : public Module
{

    using CommandCallbackFunc = std::function<void()>;

public:
    CommandCallback(ToolApplication* app_, const ToolModules& module_identity_) : Module(app_, module_identity_) { }

    virtual void OnUpdate()
    {
        std::queue<CommandEnum> localQueue;
        {   // drain queue under lock
            std::lock_guard<std::mutex> lock(mutex_);
            std::swap(localQueue, queue_);
        }

        while (!localQueue.empty())
        {
            auto cmd = localQueue.front();
            localQueue.pop();

            auto itCb = callbacks_.find(cmd);
            if(itCb != callbacks_.end())
            {
                itCb->second();
            }
            else
            {
                std::cout << "A non-registered callback tried to be executed" << std::endl; 
            }
        }
    }

    /// @brief Assign callbacks to commands
    void RegisterCommandCallback(CommandEnum cmd, CommandCallbackFunc callback)
    {
        callbacks_[cmd] = std::move(callback); 
    }

    /// @brief Enqueue commands from main to secondary threads
    void Enqueue(CommandEnum cmd)
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(cmd);
        }
    }

private:
    std::unordered_map<CommandEnum, CommandCallbackFunc> callbacks_;
    std::queue<CommandEnum> queue_;
    std::mutex mutex_;
};

}