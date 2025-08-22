#pragma once
#include <string>

namespace indra_toolkit
{
    class ToolApplication; // Forward declared!

    class Module
    {
    public:
        Module(ToolApplication* app) : tool_app(app) {}
        virtual ~Module() = default;

        virtual bool OnInit() { return true; }
        virtual void OnUpdate() {}
        virtual void OnShutdown() {}

    protected:
        ToolApplication* tool_app = nullptr;
    };
}
