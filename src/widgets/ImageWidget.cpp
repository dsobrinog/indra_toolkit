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

    // Obtener la posición actual del cursor
    ImVec2 cursorPos = ImGui::GetCursorScreenPos();

    // Mover el cursor con el offset
    ImVec2 newPos(cursorPos.x + offset.x, cursorPos.y + offset.y);
    ImGui::SetCursorScreenPos(newPos);

    // Dibujar la imagen
    ImGui::Image((void*)(intptr_t)textureID, GetPixelSize());

    // Restaurar posición para no afectar otros widgets
    ImGui::SetCursorScreenPos(cursorPos);
}
