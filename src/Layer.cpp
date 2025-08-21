#include "Layer.h"

#include <algorithm>

using namespace indra_toolkit;

void Layer::OnProcess()
{
    for (auto& pair : _widgets)
    {
        auto& widget = pair.second;
        if (widget->IsEnabled()) {
            widget->OnProcessData();
        }
    }
}

void Layer::OnRender()
{
    ImGui::Begin("Default Layer");

    for (auto& pair : _widgets)
    {
        auto& widget = pair.second;
        if (widget->IsEnabled()) {
            widget->OnRender();
        }
    }
    
    ImGui::End();
}

void Layer::AddWidget(const std::string &widget_name, std::unique_ptr<Widget> widget)
{
    _widgets.emplace_back(widget_name, std::move(widget));
}

void Layer::RemoveWidget(const std::string &name)
{
    auto it = std::remove_if(_widgets.begin(), _widgets.end(),
        [&](const auto& pair) { return pair.first == name; });

    if (it != _widgets.end())
        _widgets.erase(it, _widgets.end());
}

Widget* Layer::GetWidget(const std::string &name)
{
    for (auto& pair : _widgets)
    {
        if (pair.first == name)
            return pair.second.get();
    }
    return nullptr;
}
