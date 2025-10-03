#pragma once

#include "indra_toolkit/comms/ICommander.h"
#include "indra_toolkit/comms/IClient.h"

#include <vector>
#include <memory>
#include <iostream>


namespace indra_toolkit
{
    class ToolApplication;

    /// @brief Type-erased base class
    class IWorkerTaskBase
    {
    public:
        virtual ~IWorkerTaskBase() = default;

        virtual void Initialize() = 0;
        virtual void Tick() = 0;
        virtual void ProcessCommands() = 0;
    };

    /// @brief Templated worker task 
    /// @tparam CommandEnum custom command enum
    template<typename CommandEnum>
    class IWorkerTask : public IWorkerTaskBase
    {
    public:
        IWorkerTask(IClient* client, ToolApplication* app) 
            : _client(client), tool_app(app) { };

        virtual ~IWorkerTask() = default;

        virtual void Initialize() = 0;
        virtual void Tick() = 0;

        inline void ProcessCommands()
        {
            _commander.ProcessCommands();
        }

        inline void EnqueueCommand(CommandEnum cmd)
        {
            _commander.Enqueue(cmd);
        }

        void SetCommanderCallback(CommandCallback<CommandEnum>* commander_callback_) { _commander.SetCommanderCallback(commander_callback_); }

    protected:
        ToolApplication* tool_app;
        IClient* _client = nullptr;
        ICommander<CommandEnum> _commander;

    };
}
