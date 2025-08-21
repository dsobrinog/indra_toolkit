#pragma once

#include "Widget.h"
#include "imgui.h"

namespace indra_toolkit
{
    class TextBackgroundWidget : public Widget 
    {
        std::string m_Text;
        ImVec2 m_Size;
        ImVec4 m_BgColor;
        ImVec4 m_TextColor;


    public:
        TextBackgroundWidget(const std::string& text, ImVec2 size = ImVec2(100, 50), ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
            : m_Text(text), m_Size(size), m_BgColor(bgColor),  m_TextColor(textColor) {}

        void SetText(const std::string& text) { m_Text = text; }
        void SetSize(const ImVec2& size) { m_Size = size; }
        void SetBgColor(const ImVec4& color) { m_BgColor = color; }
        void SetTextColor(const ImVec4& color) { m_TextColor = color; }


        virtual void OnProcessData() override {}

        virtual void OnRender() override 
        {
            ImVec2 pos = ImGui::GetCursorScreenPos();   // top-left corner of widget
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            // Draw background
            draw_list->AddRectFilled(pos, ImVec2(pos.x + m_Size.x, pos.y + m_Size.y),
                                     ImGui::GetColorU32(m_BgColor));

            // Calculate text size
            ImVec2 text_size = ImGui::CalcTextSize(m_Text.c_str());

            // Calculate centered position
            ImVec2 text_pos = ImVec2(
                pos.x + (m_Size.x - text_size.x) * 0.5f,
                pos.y + (m_Size.y - text_size.y) * 0.5f
            );

            // Draw text with editable color
            draw_list->AddText(text_pos, ImGui::GetColorU32(m_TextColor), m_Text.c_str());

            // Reserve space so layout continues correctly
            ImGui::Dummy(m_Size);
        }
    };
}
