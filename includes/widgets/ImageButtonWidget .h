#pragma once

#include "imgui.h"
#include "Widget.h"
#include <functional>

namespace indra_toolkit
{
    // Image Button widget
    class ImageButtonWidget : public Widget
    {
    public:
        ImageButtonWidget(ImTextureID texture, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1))
            : texture(texture), size(size), uv0(uv0), uv1(uv1) {}

        virtual void OnRender() override
        {
            if (!enable || texture == ImTextureID_Invalid) return;

            // if (ImGui::ImageButton(texture, size, uv0, uv1))
            // {
            //     if (onClick) onClick();
            // }
        }

        void SetTexture(ImTextureID tex) { texture = tex; }
        void SetSize(const ImVec2& newSize) { size = newSize; }

        void SetOnClick(std::function<void()> callback) { onClick = callback; }

    private:
        ImTextureID texture;
        ImVec2 size;
        ImVec2 uv0, uv1;
        std::function<void()> onClick;
    };
}