#include "indra_toolkit/layers/InteractiveLayer.h"
#include "indra_toolkit/ToolApplication.h"
#include "indra_toolkit/Widget.h"

namespace indra_toolkit
{
    void InteractiveLayer::OnProcess()
    {
        for(int i = 0; i < _widgets.size(); ++i)
        {
            if(_widgets[i]->IsEnabled())
            {
                _widgets[i]->OnProcessData();
            }
        }
    }

    void InteractiveLayer::OnRender()
    {
        // // Full GLFW window (TO DO: editable)
        SetSize(tool_app->GetMainWindowSize());

        // Set a window that covers the entire viewport
        ImGui::SetNextWindowPos(_position);
        ImGui::SetNextWindowSize(_size);

        ImGui::PushStyleColor(ImGuiCol_WindowBg, _bgColor);                 // background color
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, _windowRounding); // rounded corners
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, _windowPadding);   // padding?

        ImGui::Begin(layer_name.c_str(), nullptr, window_flags);
        
        for(int i = 0; i < _widgets.size(); ++i)
        {
            if(_widgets[i]->IsEnabled())
            {
                _widgets[i]->OnRender();

            }
        }

        ImGui::End();

        ImGui::PopStyleVar(2);   // pop the two style vars
        ImGui::PopStyleColor();  // pop the window bg color
    }
}