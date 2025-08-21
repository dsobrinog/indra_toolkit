#pragma once

#include "imgui.h"
#include "Widget.h"

namespace indra_toolkit
{
    // Basic Image widget
    class ImageWidget : public Widget
    {
    public:
        ImageWidget(ImTextureID* texture, const ImVec2& size)
            : texture(texture), size(size) {}

        virtual void OnRender() override;

        void SetTexture(ImTextureID* tex) { texture = tex; }
        void SetSize(const ImVec2& newSize) { size = newSize; }

    private:
        ImTextureID* texture;
        ImVec2 size;
    };
}