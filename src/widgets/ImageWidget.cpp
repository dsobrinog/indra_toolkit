#include "indra_toolkit/widgets/ImageWidget.h"
#include <iostream>

using namespace indra_toolkit;

ImageWidget::ImageWidget(ImageLoader* loader, const std::string& pathToImage, const ImVec2& size)
    : image_loader(loader)
{
    SetSize(size);
    int width, height;
    textureID = image_loader->LoadTexture(pathToImage, &width, &height);

    if (textureID == 0) {
        std::cerr << "ImageWidget: failed to load " << pathToImage << std::endl;
    }
    else if (GetSize().x != width || GetSize().y != height) {
        std::cout << "Warning: image size " << width << "x" << height 
                  << " differs from widget size " << GetSize().x << "x" << GetSize().y << std::endl;
    }
}

ImageWidget::~ImageWidget()
{
    // Do NOT delete texture here, ImageLoader owns it
}

void ImageWidget::Draw()
{
    if (!IsEnabled() || textureID == 0) return;
    ImGui::Image((void*)(intptr_t)textureID, GetPixelSize());
}
