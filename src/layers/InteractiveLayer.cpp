#include "indra_toolkit/layers/InteractiveLayer.h"
#include "indra_toolkit/ToolApplication.h"
#include "indra_toolkit/Widget.h"

namespace indra_toolkit
{
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
        
        for (auto& w : _widgets)
        {
            if (w->IsEnabled())
                w->OnRender();
        }

        ImGui::End();

        ImGui::PopStyleVar(2);   // pop the two style vars
        ImGui::PopStyleColor();  // pop the window bg color
    }
}