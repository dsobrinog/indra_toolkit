#pragma once

#include "indra_toolkit/Layer.h"
#include "indra_toolkit/layers/BackgroundLayer.h"
#include "indra_toolkit/Widget.h"

namespace indra_toolkit
{
    class InteractiveLayer : public Layer
    {
        public:
            InteractiveLayer(ToolApplication* app) : Layer(app) {}
            InteractiveLayer(std::string& layer_name, ImVec2& size, ImVec2& pos, ImVec4& color, ImGuiWindowFlags flags) : Layer(layer_name, size, pos){}
            ~InteractiveLayer() {}

            virtual void OnProcess(){};
            virtual void OnRender()
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
                // ImGui::Begin(layer_name.c_str(), nullptr);

                for (auto& w : _widgets)
                {
                    if (w->IsEnabled())
                        w->OnRender();
                }

                ImGui::End();

                ImGui::PopStyleVar(2);   // pop the two style vars
                ImGui::PopStyleColor();  // pop the window bg color
            };

            inline void SetBackgroundColor(const ImVec4& color) { _bgColor = color; }
            inline void SetWindowRounding(float rounding) { _windowRounding = rounding; }
            inline void SetWindowPadding(const ImVec2& padding) { _windowPadding = padding; }
            inline void SetWindowFlags(ImGuiWindowFlags& flags){ window_flags = flags; }

        protected:
            ImVec4 _bgColor = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
            float _windowRounding = 12.0f;
            ImVec2 _windowPadding = ImVec2(16, 16);

            ImGuiWindowFlags window_flags = 
                                            ImGuiWindowFlags_NoTitleBar 
                                          | ImGuiWindowFlags_NoResize 
                                          | ImGuiWindowFlags_NoMove 
                                          | ImGuiWindowFlags_NoCollapse 
                                          | ImGuiWindowFlags_NoBringToFrontOnFocus;
    };
}