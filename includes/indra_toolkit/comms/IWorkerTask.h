#pragma once

#include "indra_toolkit/comms/ICommand.h"
#include "indra_toolkit/comms/IClient.h"
#include <vector>
#include <memory>

namespace indra_toolkit
{
    class IWorkerTask
    {
    public:
        IWorkerTask(IClient* client) 
            : _client(client) {};
        virtual ~IWorkerTask() = default;

        virtual void Tick() = 0;

        inline void ProcessCommands()
        {
            for(auto& c : commands_)
                c->ExecuteCommand();
        }

        inline void AddCommand(std::unique_ptr<ICommand> command) {
            commands_.push_back(std::move(command));
        }

    protected:
        std::vector<std::unique_ptr<ICommand>> commands_;
        IClient* _client = nullptr;
    };
}
