#pragma once

#include "indra_toolkit/Layer.h"

namespace indra_toolkit
{
    class InteractiveLayer : public Layer
    {
        public:
            InteractiveLayer(ToolApplication* app) : Layer(app) {}
            ~InteractiveLayer() {}

            virtual void OnProcess(){};
            virtual void OnRender();

            inline void SetBackgroundColor(const ImVec4& color) { _bgColor = color; }
            inline void SetWindowRounding(float rounding) { _windowRounding = rounding; }
            inline void SetWindowPadding(const ImVec2& padding) { _windowPadding = padding; }
            inline void SetWindowFlags(ImGuiWindowFlags flags){ window_flags = flags; }

        protected:
            ImVec4 _bgColor = ImVec4(0.1f, 0.1f, 0.1f, 1.f);
            float _windowRounding = 12.0f;
            ImVec2 _windowPadding = ImVec2(16, 16);

            ImGuiWindowFlags window_flags = 
                                            ImGuiWindowFlags_NoTitleBar 
                                          | ImGuiWindowFlags_NoResize 
                                          | ImGuiWindowFlags_NoMove 
                                          | ImGuiWindowFlags_NoCollapse 
                                          | ImGuiWindowFlags_NoBringToFrontOnFocus
                                          | ImGuiWindowFlags_NoScrollbar
                                          | ImGuiWindowFlags_MenuBar;
    };
}