#pragma once

#include "Widget.h"

namespace indra_toolkit
{
    class VerticalSpacer : public Widget
    {
    public:
        VerticalSpacer(float height) : _height(height) {}

        virtual void OnRender() override 
        {
            ImGui::Dummy(ImVec2(0.0f, _height)); // Empty space
        }

    private:
        float _height;
    };

    class SeparatorWidget : public Widget
    {
    public:
        virtual void OnRender() override 
        {
            ImGui::Separator();
        }
    };

    class SpacerWidget : public Widget
    {
    public:
        SpacerWidget(int times):spaces(times){}

        virtual void OnRender() override 
        {
            for (size_t i = 0; i < spaces; i++)
            {
                 ImGui::Spacing();
            }
        }
        
    private:
        int spaces = 0;
    };
}
