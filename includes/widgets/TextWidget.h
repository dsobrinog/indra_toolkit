
#pragma once

#include "Widget.h"

namespace indra_toolkit
{
    class TextWidget : public Widget 
    {
        std::string m_Text;
        ImVec2 m_Size;
    
    public:
        TextWidget(const std::string& text) : m_Text(text) {}
        void SetText(const std::string& text) { m_Text = text; }
        
        void SetSize(const ImVec2 size) {m_Size = size; }

        virtual void OnProcessData(){};
        virtual void OnRender() override {
            // ImGui::LabelText(m_Text.c_str(), "lorem ipsum");
            ImGui::TextUnformatted(m_Text.c_str());
        }
    };

}
