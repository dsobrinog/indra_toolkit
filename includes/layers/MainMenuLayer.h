#pragma once

#include "Layer.h"
#include "Widget.h"

namespace indra_toolkit
{
    class MainMenuLayer : public Layer
    {
        public:
            MainMenuLayer() : Layer() {}
            ~MainMenuLayer() {}

            virtual void OnProcess(){};
            virtual void OnRender()
            {
                ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar 
                           | ImGuiWindowFlags_NoResize 
                           | ImGuiWindowFlags_NoMove 
                           | ImGuiWindowFlags_NoCollapse 
                           | ImGuiWindowFlags_NoBackground; // invisible background

                ImGui::Begin("MainMenu", nullptr, flags);

                for (auto& pair : _widgets)
                {
                    auto& w = pair.second;
                    if (w->IsEnabled())
                        w->OnRender();
                }
                
                ImGui::End();
            };
    };
}