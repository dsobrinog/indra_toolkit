#pragma once

#include "indra_toolkit/Module.h"
#include "indra_toolkit/layers/InteractiveLayer.h"

namespace indra_toolkit
{

    /// @brief Contains functionality for searching folders, choosing files, etc.
    class FileExplorer : public Module
    {
    public:
        FileExplorer(ToolApplication* app_, const ToolModules& moduleIdentity_) : Module(app_, moduleIdentity_){}

        virtual bool OnInit() override;
        virtual void OnUpdate() override;
        virtual void OnShutdown() override;

        virtual bool IsDeferred() const { return true; }

    private:
        InteractiveLayer* interactive_layer = nullptr;
    };
}