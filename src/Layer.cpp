#include "indra_toolkit/Layer.h"
#include "indra_toolkit/ToolApplication.h"

#include <algorithm>

using namespace indra_toolkit;

Layer::Layer(ToolApplication* app)
    : tool_app(app)
{     
    draw_debug = tool_app->IsDebugEnabled(); 
}

void Layer::OnProcess()
{
    for (auto& widget : _widgets)
    {
        if (widget->IsEnabled()) {
            widget->OnProcessData();
        }
    }
}

void Layer::OnRender()
{
    ImGui::Begin("Default Layer");

    for (auto& widget : _widgets)
    {
        if (widget->IsEnabled()) {
            widget->OnRender();
        }
    }
    
    ImGui::End();
}

bool indra_toolkit::Layer::IsDebugEnabled() const
{
    bool debugEnabledInApp = tool_app->IsDebugEnabled();
    return debugEnabledInApp && IsEnabled() && draw_debug;
}

void indra_toolkit::Layer::RemoveWidget(Widget* widget)
{
    auto it = std::remove_if(
        _widgets.begin(),
        _widgets.end(),
        [widget](const std::unique_ptr<Widget>& ptr) {
            return ptr.get() == widget;
        });

    if (it != _widgets.end())
    {
        _widgets.erase(it, _widgets.end()); // Delete all matches
    }
}