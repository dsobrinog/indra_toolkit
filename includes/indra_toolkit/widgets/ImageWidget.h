#pragma once
#include "imgui.h"
#include "indra_toolkit/Widget.h"
#include "indra_toolkit/modules/resource_management/image/ImageLoader.h"

namespace indra_toolkit
{
    class ImageWidget : public Widget
    {
    public:
        ImageWidget(ImageLoader* loader, const std::string& pathToImage, const ImVec2& size);
        virtual ~ImageWidget();

        virtual void Draw() override;

        void SetOffset(const ImVec2& offset_) { offset = offset_; }
        void SetOffset(float x, float y) { offset = ImVec2(x, y); }
        ImVec2 GetOffset() const { return offset; }

    private:
        ImageLoader* image_loader = nullptr;
        GLuint textureID = 0;
        ImVec2 offset = ImVec2(0, 0);
    };
}
