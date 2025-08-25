#include "Layer.h"

#include "ToolApplication.h"
#include <algorithm>

using namespace indra_toolkit;

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