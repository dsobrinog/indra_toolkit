#pragma once
#include <string>
#include "CommonDefinitions.h"

namespace indra_toolkit
{
    class ToolApplication; // Forward declared!

    class Module
    {
    public:
        Module(ToolApplication* app_, const ToolModules& module_identity_) : tool_app(app_), module_identity(module_identity_) {}
        virtual ~Module() = default;

        virtual bool OnInit() { return true; }
        virtual void OnUpdate() {}
        virtual void OnShutdown() {}

        ToolModules GetIdentity() const { return module_identity; }

    protected:
        ToolApplication* tool_app = nullptr;

    private:
        ToolModules module_identity;    //can only set this in constructor. Shouldn´t be able to change it.
    };
}
