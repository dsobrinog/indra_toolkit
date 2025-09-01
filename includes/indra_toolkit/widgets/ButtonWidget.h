#pragma once

#include "indra_toolkit/Widget.h"

#include <functional>
#include <string>

namespace indra_toolkit
{
    class ButtonWidget : public Widget 
    {
        
    public:
        ButtonWidget(const std::string& label, std::function<void()> callback)
            : m_Label(label), m_Callback(callback) {}

        virtual void OnProcessData() override {};
        virtual void OnRender() override;

        // Setters for customization
        ButtonWidget& SetSize(const ImVec2& size) { m_Size = size; return *this; }
        ButtonWidget& SetBgColor(const ImVec4& color) { m_BgColor = color; return *this; }
        ButtonWidget& SetTextColor(const ImVec4& color) { m_TextColor = color; return *this; }
        ButtonWidget& SetFlags(int flags) { m_Flags = flags; return *this; }

    protected:
        std::string m_Label;
        std::function<void()> m_Callback;

        // Customizable properties
        ImVec2 m_Size = ImVec2(0, 0);        // Default = auto size
        ImVec4 m_BgColor = ImVec4(0, 0, 0, 0); // Transparent (no override)
        ImVec4 m_TextColor = ImVec4(1, 1, 1, 1); // White text
        int m_Flags = 0;                      // Reserved for future ImGui flags
    };
}
