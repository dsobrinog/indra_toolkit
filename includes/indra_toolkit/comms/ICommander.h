#pragma once
#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>

#include "indra_toolkit/modules/command_callbacks/CommandCallback.h"

namespace indra_toolkit
{
    /// @brief Register commands at start, push commands runtime from main thread and secondary thread will consume them
    /// @tparam CommandEnum custom command enum
    template<typename CommandEnum>
    class ICommander
    {
    public:
        using CommandHandler = std::function<void()>;
        

        /// @brief Assign callbacks to commands
        void RegisterCommand(CommandEnum cmd, CommandHandler handler)
        {
            handlers_[cmd] = std::move(handler);
        }

        /// @brief Enqueue commands from main to secondary threads
        void Enqueue(CommandEnum cmd)
        {
            {
                std::lock_guard<std::mutex> lock(mutex_);
                queue_.push(cmd);
            }
            cond_.notify_one();
        }

        /// @brief Consume all commands that are enqueued
        void ProcessCommands()
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

                auto it = handlers_.find(cmd);
                if (it != handlers_.end())
                {
                    it->second(); // execute registered handler 
                }
                else
                {
                    std::cerr << " ICommander: You are trying to execute a command that is not registered!!" << std::endl;
                }

                if(commander_callback) commander_callback->Enqueue(cmd); //execute callback if we have it
            }
        }

        void SetCommanderCallback(CommandCallback<CommandEnum>* commander_callback_) { commander_callback = commander_callback_; }

    private:
        std::unordered_map<CommandEnum, CommandHandler> handlers_;
        std::queue<CommandEnum> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
        CommandCallback<CommandEnum>* commander_callback;
    };
}
