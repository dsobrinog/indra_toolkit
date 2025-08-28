#pragma once

#include "Widget.h"
#include "imgui.h"

namespace indra_toolkit
{
    class TextBackgroundWidget : public Widget 
    {
        TextWidget m_TextWidget;
        
        ImVec2 m_Size;
        ImVec4 m_BgColor;
        ImVec4 m_TextColor;

    public:

        /// @brief Create a text with background
        /// @param text text to display
        /// @param size size of the background
        /// @param bgColor color of the background
        /// @param textColor color of the text
        TextBackgroundWidget(const std::string& text,                                       
                             ImVec2 size = ImVec2(100, 50),                                 
                             ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f),               
                             ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f))             
            : m_TextWidget(text), m_Size(size), m_BgColor(bgColor), m_TextColor(textColor)
        {}

        /// @brief Creates a dynamic text with background
        /// @param textPtr pointer to the dynamic text
        /// @param size size of the background
        /// @param bgColor color of the background
        /// @param textColor color of the text
        TextBackgroundWidget(const std::string* textPtr,
                             ImVec2 size = ImVec2(100, 50),
                             ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f),
                             ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f))
            : m_TextWidget(textPtr), m_Size(size), m_BgColor(bgColor), m_TextColor(textColor)
        {}
            
        inline void SetText(const std::string& text) { m_TextWidget.SetText(text); }
        inline void SetDynamicText(const std::string* textPtr) { m_TextWidget.SetDynamicText(textPtr); }
        inline void SetSize(const ImVec2& size) { m_Size = size; }
        inline void SetBgColor(const ImVec4& color) { m_BgColor = color; }
        inline void SetTextColor(const ImVec4& color) { m_TextColor = color; }


        virtual void OnProcessData() override 
        {
            m_TextWidget.OnProcessData();
        }

        virtual void OnRender() override 
        {
            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            // Draw background
            draw_list->AddRectFilled(pos, ImVec2(pos.x + m_Size.x, pos.y + m_Size.y),
                                     ImGui::GetColorU32(m_BgColor));

            // Draw text using TextWidget
            ImVec2 text_size = ImGui::CalcTextSize(m_TextWidget.GetText().c_str());
            ImVec2 text_pos = ImVec2(
                pos.x + (m_Size.x - text_size.x) * 0.5f,
                pos.y + (m_Size.y - text_size.y) * 0.5f
            );
            draw_list->AddText(text_pos, ImGui::GetColorU32(m_TextColor),
                               m_TextWidget.GetText().c_str());

            ImGui::Dummy(m_Size);
        }
    };
}
