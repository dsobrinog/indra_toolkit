#include "indra_toolkit/widgets/ImageButtonWidget.h"
#include <iostream>

namespace indra_toolkit
{
    // --- Basic constructor ---
    ImageButtonWidget::ImageButtonWidget(ImageLoader* loader,
                                         const std::string& pathToImage,
                                         const ImVec2& size)
        : Widget(PositionVars(), ""),
          image_loader(loader),
          size(size),
          uv0(ImVec2(0, 0)),
          uv1(ImVec2(1, 1))
    {
        LoadTexture(size, pathToImage);
    }

    // --- With UVs ---
    ImageButtonWidget::ImageButtonWidget(ImageLoader* loader,
                                         const std::string& pathToImage,
                                         const ImVec2& size,
                                         const ImVec2& uv0,
                                         const ImVec2& uv1)
        : Widget(PositionVars(), ""),
          image_loader(loader),
          size(size),
          uv0(uv0),
          uv1(uv1)
    {
        LoadTexture(size, pathToImage);
    }

    // --- With posVars + widgetName ---
    ImageButtonWidget::ImageButtonWidget(ImageLoader* loader,
                                         const std::string& pathToImage,
                                         const ImVec2& size,
                                         const PositionVars& posVars,
                                         const std::string& widgetName)
        : Widget(posVars, widgetName),
          image_loader(loader),
          size(size),
          uv0(ImVec2(0, 0)),
          uv1(ImVec2(1, 1))
    {
        LoadTexture(size, pathToImage);
    }

    // --- Full constructor ---
    ImageButtonWidget::ImageButtonWidget(ImageLoader* loader,
                                         const std::string& pathToImage,
                                         const ImVec2& size,
                                         const ImVec2& uv0,
                                         const ImVec2& uv1,
                                         const PositionVars& posVars,
                                         const std::string& widgetName)
        : Widget(posVars, widgetName),
          image_loader(loader),
          size(size),
          uv0(uv0),
          uv1(uv1)
    {
        LoadTexture(size, pathToImage);
    }

    // --- With callback directly ---
    ImageButtonWidget::ImageButtonWidget(ImageLoader* loader,
                                         const std::string& pathToImage,
                                         const ImVec2& size,
                                         std::function<void()> callback)
        : Widget(PositionVars(), ""),
          image_loader(loader),
          size(size),
          uv0(ImVec2(0, 0)),
          uv1(ImVec2(1, 1)),
          onClick(callback)
    {
        LoadTexture(size, pathToImage);
    }

    // --- Load texture ---
    void ImageButtonWidget::LoadTexture(const ImVec2& size, const std::string& pathToImage)
    {
        SetSize(size);
        int width = 0, height = 0;
        textureID = image_loader->LoadTexture(pathToImage, &width, &height);

        if (textureID == 0)
        {
            std::cerr << "ImageButtonWidget: failed to load " << pathToImage << std::endl;
        }
        else if (GetSize().x != width || GetSize().y != height)
        {
            std::cout << "Warning: image size " << width << "x" << height
                      << " differs from widget size " << GetSize().x << "x" << GetSize().y << std::endl;
        }
    }

    // --- Draw ---
    void ImageButtonWidget::Draw()
    {
        if (!IsEnabled() || textureID == 0)
            return;

        if(type == ButtonType::Full_Image)
            FullImageDraw();
        else
            RelativeImageDraw();
    }

 
    void ImageButtonWidget::FullImageDraw()
    {
        // Push style so text and image can overlap
        ImGui::PushID(this); // ensure unique ID
        ImGui::BeginGroup();

        if (ImGui::ImageButton(GetWidgetName().c_str(),
                               (ImTextureID)(intptr_t)textureID,
                               size, uv0, uv1))
        {
            if (onClick)
                onClick();
        }

        // Draw text centered over button
        if (!m_Text.empty())
        {
            ImVec2 textSize   = ImGui::CalcTextSize(m_Text.c_str());
            ImVec2 buttonPos  = ImGui::GetItemRectMin();
            ImVec2 buttonSize = ImGui::GetItemRectSize();
            ImVec2 textPos    = ImVec2(
                buttonPos.x + (buttonSize.x - textSize.x) * 0.5f,
                buttonPos.y + (buttonSize.y - textSize.y) * 0.5f);

            ImGui::GetWindowDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), m_Text.c_str());
        }

        ImGui::EndGroup();
        ImGui::PopID();
    }


    bool initial_draw = true;
    float originalXSize = 0;
    float originalYSize = 0;

    // proporciones relativas de la imagen
    float relativeX = 0.0f;
    float relativeY = 0.0f;
    float relativeW = 0.0f;
    float relativeH = 0.0f;

    void ImageButtonWidget::RelativeImageDraw()
    {
        if(initial_draw)
        {
            initial_draw = false;
            originalXSize = GetPixelSize().x;
            originalYSize = GetPixelSize().y;

            // Guardamos proporciones relativas respecto al botón inicial
            relativeX = m_ImageOffset.x / originalXSize;
            relativeY = m_ImageOffset.y / originalYSize;
            relativeW = m_ImageSize.x   / originalXSize;
            relativeH = m_ImageSize.y   / originalYSize;
        }

        ImGui::PushID(this);

        // Calcular factores de escala respecto al tamaño original
        float scaleFactorX = GetPixelSize().x / originalXSize;
        float scaleFactorY = GetPixelSize().y / originalYSize;
        float finalScaleFactor = std::min(scaleFactorX, scaleFactorY); 
        // uso min() para que no se deforme demasiado el texto

        // Draw the actual clickable button
        ImGui::PushStyleColor(ImGuiCol_Button, m_BgColor);
        ImGui::PushStyleColor(ImGuiCol_Text, m_TextColor);

        // Escalar el texto SOLO para este botón
        ImGui::SetWindowFontScale(finalScaleFactor);

        if (ImGui::Button(GetWidgetName().c_str(), GetPixelSize()))
        {
            if (onClick) onClick();
        }

        // Restaurar el tamaño original de la fuente
        ImGui::SetWindowFontScale(1.0f);

        ImGui::PopStyleColor(2);

        ImVec2 buttonPos  = ImGui::GetItemRectMin();
        ImVec2 buttonSize = ImGui::GetItemRectSize();

        // Recalcular posición y tamaño de la imagen según las proporciones
        if (textureID != 0)
        {
            ImVec2 imgPos, imgEnd;

            if (scale_enable)
            {
                // Escalado proporcional al tamaño del botón
                imgPos = ImVec2(buttonPos.x + buttonSize.x * relativeX,
                                buttonPos.y + buttonSize.y * relativeY);

                imgEnd = ImVec2(imgPos.x + buttonSize.x * relativeW,
                                imgPos.y + buttonSize.y * relativeH);
            }
            else
            {
                // Mantener tamaño original de la imagen (no escalar)
                imgPos = ImVec2(buttonPos.x + buttonSize.x * relativeX,
                                buttonPos.y + buttonSize.y * relativeY);

                imgEnd = ImVec2(imgPos.x + m_ImageSize.x,
                                imgPos.y + m_ImageSize.y);
            }

            ImGui::GetWindowDrawList()->AddImage(
                (ImTextureID)(intptr_t)textureID,
                imgPos,
                imgEnd,
                uv0,
                uv1,
                ImColor(m_ImageTint.x, m_ImageTint.y, m_ImageTint.z, m_ImageTint.w)
            );
        }

        ImGui::PopID();
    }



    // --- Setters ---
    void ImageButtonWidget::SetTexture(GLuint tex)
    {
        textureID = tex;
    }

    void ImageButtonWidget::SetSize(const ImVec2& newSize)
    {
        size = newSize;
    }

    void ImageButtonWidget::SetOnClick(std::function<void()> callback)
    {
        onClick = callback;
    }
}
