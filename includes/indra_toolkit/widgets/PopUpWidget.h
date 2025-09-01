#pragma once

#include "indra_toolkit/Widget.h"

namespace indra_toolkit
{
    class PopUpWidget : public Widget
    {
    public:
        PopUpWidget(const std::string& name)
            : popup_name(name)
        {}

        // Called when you want to open the popup
        void Open() { ImGui::OpenPopup(popup_name.c_str()); }

        // Called when you want to close from code (alternative to user clicking)
        void Close() { ImGui::CloseCurrentPopup(); }

        void OnRender() override
        {
            // Set desired size and position before opening
            ImGui::SetNextWindowSize(ImVec2(150, 50), ImGuiCond_None);
            ImGui::SetNextWindowPos(ImVec2(200, 100), ImGuiCond_None);

            if (ImGui::BeginPopup(popup_name.c_str()))
            {
                RenderContent();
                ImGui::EndPopup();
            }
        }

    protected:
        // Derived popups override this
        virtual void RenderContent()
        {
            ImGui::Text("Empty Popup");
            if (ImGui::Button("Close"))
                ImGui::CloseCurrentPopup();
        }

    private:
        std::string popup_name;
    };
}
