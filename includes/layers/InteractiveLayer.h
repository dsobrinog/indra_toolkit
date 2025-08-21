#pragma once

#include "Layer.h"
#include "BackgroundLayer.h"
#include "Widget.h"

namespace indra_toolkit
{
    class InteractiveLayer : public BackgroundLayer
    {
        public:
            InteractiveLayer() : Layer(), BackgroundLayer() {}
            ~InteractiveLayer() {}

            virtual void OnProcess(){};
            virtual void OnRender()
            { 
               // Set a window that covers the entire viewport
                ImGui::SetNextWindowPos(_position);
                ImGui::SetNextWindowSize(_size);

                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar 
                                    | ImGuiWindowFlags_NoResize 
                                    | ImGuiWindowFlags_NoMove 
                                    | ImGuiWindowFlags_NoCollapse 
                                    // | ImGuiWindowFlags_NoBackground
                                    | ImGuiWindowFlags_NoBringToFrontOnFocus;   // <-


                ImGui::PushStyleColor(ImGuiCol_WindowBg, _bgColor);  // dark semi-transparent
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, _windowRounding);                   // rounded corners
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, _windowPadding);

                ImGui::Begin("Interactive Layer", nullptr, flags);

                for (auto& pair : _widgets)
                {
                    auto& w = pair.second;
                    if (w->IsEnabled())
                        w->OnRender();
                }

                ImGui::End();

                ImGui::PopStyleVar(2);   // pop the two style vars
                ImGui::PopStyleColor();  // pop the window bg color
            };

         
    };
}