#pragma once

#include "indra_toolkit/Widget.h"
#include <string>
#include <functional>
#include "imgui.h"

namespace indra_toolkit
{
    class TooltipWidget : public Widget
    {
    public:
        // Constructor
        TooltipWidget(const std::string& name, const std::string& text)
            : tooltip_name(name), tooltip_text(text)
        {}

        TooltipWidget(const char* name, const char* text)
            : tooltip_name(std::string(name)), tooltip_text(std::string(text)) {}

        // Optional: constructor with dynamic text provider
        TooltipWidget(const std::string& name, std::function<std::string()> dynamic_text)
            : tooltip_name(name), text_provider(dynamic_text)
        {}

        // Set tooltip text dynamically
        void SetText(const std::string& text) { tooltip_text = text; }

        // Enable dynamic text provider
        void SetDynamicTextProvider(std::function<std::string()> provider) { text_provider = provider; }
        
        void Draw() override
        {
            if (!IsEnabled())
                return;

            // If hovering, show tooltip
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                if (text_provider)
                    ImGui::TextUnformatted(text_provider().c_str());
                else
                    ImGui::TextUnformatted(tooltip_text.c_str());
                ImGui::EndTooltip();
            }
        }

    protected:
        std::string tooltip_name;  // Widget identifier
        std::string tooltip_text;  // Static tooltip text
        std::function<std::string()> text_provider;  // Optional dynamic text
    };
}
