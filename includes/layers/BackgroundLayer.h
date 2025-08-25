#pragma once

#include "imgui.h"
#include "Layer.h"
#include "Widget.h"

namespace indra_toolkit
{
    class BackgroundLayer : public virtual Layer
    {
        public:
            BackgroundLayer(ToolApplication* app) : Layer(app) {}
            ~BackgroundLayer() {}

            virtual void OnProcess(){};
            virtual void OnRender()
            {
                // Set a window that covers the entire viewport
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);

                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar 
                                    | ImGuiWindowFlags_NoResize 
                                    | ImGuiWindowFlags_NoMove 
                                    | ImGuiWindowFlags_NoCollapse 
                                    | ImGuiWindowFlags_NoInputs; 

                // _bgColor = ImVec4(1.0f, 1.0f, 0.2f, 1.0f); // bright yellow, fully opaque
                ImGui::PushStyleColor(ImGuiCol_WindowBg, _bgColor);  // dark semi-transparent
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, _windowRounding);                   // rounded corners
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, _windowPadding);

                ImGui::Begin("BackgroundLayer", nullptr, flags);

                for (auto& w : _widgets)
                {
                    if (w->IsEnabled())
                        w->OnRender();
                }

                ImGui::End();

                ImGui::PopStyleVar(2);   // pop the two style vars
                ImGui::PopStyleColor();  // pop the window bg color
        };

            void SetBackgroundColor(const ImVec4& color) { _bgColor = color; }
            void SetWindowRounding(float rounding) { _windowRounding = rounding; }
            void SetWindowPadding(const ImVec2& padding) { _windowPadding = padding; }

        protected:
        
            ImVec4 _bgColor = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
            float _windowRounding = 12.0f;
            ImVec2 _windowPadding = ImVec2(16, 16);
    };
}