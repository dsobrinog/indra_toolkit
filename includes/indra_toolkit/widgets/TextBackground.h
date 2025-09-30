#pragma once

#include "indra_toolkit/Widget.h"
#include "imgui.h"

namespace indra_toolkit
{
    class TextBackgroundWidget : public Widget 
    {
        TextWidget m_TextWidget;
        
        ImVec4 m_BgColor;
        ImVec4 m_TextColor;
        ImVec2 m_Offset;

    public:

        /// @brief Create a text with background
        /// @param text text to display
        /// @param size size of the background
        /// @param bgColor color of the background
        /// @param textColor color of the text
        TextBackgroundWidget(const std::string& text,                                       
                             ImVec2 size = ImVec2(100, 50),                                 
                             ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f),               
                             ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                             ImVec2 offset_ = ImVec2(0, 0))
           
            : m_TextWidget(text), m_BgColor(bgColor), m_TextColor(textColor), m_Offset(offset_)
        {}

        /// @brief Creates a dynamic text with background
        /// @param textPtr pointer to the dynamic text
        /// @param size size of the background
        /// @param bgColor color of the background
        /// @param textColor color of the text
        TextBackgroundWidget(const std::string* textPtr,
                             ImVec2 size = ImVec2(100, 50),
                             ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f),
                             ImVec4 textColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                             ImVec2 offset_ = ImVec2(0, 0))
            : m_TextWidget(textPtr), m_BgColor(bgColor), m_TextColor(textColor), m_Offset(offset_)
        {}

        inline void SetOffset(const ImVec2& offset_) { m_Offset = offset_; }
        inline void SetText(const std::string& text) { m_TextWidget.SetText(text); }
        inline void SetDynamicText(const std::string* textPtr) { m_TextWidget.SetDynamicText(textPtr); }
        inline void SetBgColor(const ImVec4& color) { m_BgColor = color; }
        inline void SetTextColor(const ImVec4& color) { m_TextColor = color; }


        virtual void OnProcessData() override 
        {
            m_TextWidget.OnProcessData();
        }

        virtual void Draw() override 
        {
            ImVec2 pos = ImGui::GetCursorScreenPos();
            pos.x += m_Offset.x;
            pos.y += m_Offset.y;

            ImDrawList* draw_list = ImGui::GetWindowDrawList();

            // Background
            draw_list->AddRectFilled(pos, ImVec2(pos.x + GetPixelSize().x, pos.y + GetPixelSize().y),
                                    ImGui::GetColorU32(m_BgColor));

            // Centered text
            ImVec2 text_size = ImGui::CalcTextSize(m_TextWidget.GetText().c_str());
            ImVec2 text_pos(
                pos.x + (GetPixelSize().x - text_size.x) * 0.5f,
                pos.y + (GetPixelSize().y - text_size.y) * 0.5f
            );
            draw_list->AddText(text_pos, ImGui::GetColorU32(m_TextColor),
                            m_TextWidget.GetText().c_str());

            ImGui::Dummy(GetPixelSize());
        }
    };
}
