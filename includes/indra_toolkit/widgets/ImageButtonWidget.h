#pragma once

#include "imgui.h"
#include <functional>
#include <string>
#include "indra_toolkit/Widget.h"
#include "indra_toolkit/modules/resource_management/image/ImageLoader.h"

namespace indra_toolkit
{
    class ImageButtonWidget : public Widget
    {
    public:
        // Basic: loader + path + size
        ImageButtonWidget(ImageLoader* loader,
                          const std::string& pathToImage,
                          const ImVec2& size);

        // With UVs
        ImageButtonWidget(ImageLoader* loader,
                          const std::string& pathToImage,
                          const ImVec2& size,
                          const ImVec2& uv0,
                          const ImVec2& uv1);

        // With posVars + widgetName
        ImageButtonWidget(ImageLoader* loader,
                          const std::string& pathToImage,
                          const ImVec2& size,
                          const PositionVars& posVars,
                          const std::string& widgetName);

        // Full (UVs + posVars + widgetName)
        ImageButtonWidget(ImageLoader* loader,
                          const std::string& pathToImage,
                          const ImVec2& size,
                          const ImVec2& uv0,
                          const ImVec2& uv1,
                          const PositionVars& posVars,
                          const std::string& widgetName);

        // With callback directly
        ImageButtonWidget(ImageLoader* loader,
                          const std::string& pathToImage,
                          const ImVec2& size,
                          std::function<void()> callback);

        void LoadTexture(const ImVec2& size, const std::string& pathToImage);
        virtual void Draw() override;

        void FullImageDraw();
        void RelativeImageDraw();

        enum ButtonType{ Full_Image, Relative_Image} type;
        /// @brief Set the type of button image: 
        /// @param _type Image_Full: The icon size is equal to button size. Relative_Image: You specify button size, image size and place image with an offset
        inline void SetButtonType(ButtonType _type){ type = _type;}

        void SetTexture(GLuint tex);
        void SetSize(const ImVec2& newSize);
        void SetOnClick(std::function<void()> callback);
        void SetText(const std::string& text) { m_Text = text; }

        

        // Image relative
        void SetImageSize(const ImVec2& size) { m_ImageSize = size; }
        void SetImageOffset(const ImVec2& offset) { m_ImageOffset = offset; }
        void SetImageTint(const ImVec4& tint) { m_ImageTint = tint; }
        inline void SetScale(bool enable){ scale_enable = enable; };
        // Button
        void SetButtonBgColor(const ImVec4& color) { m_BgColor = color; }
        void SetButtonTextColor(const ImVec4& color) { m_TextColor = color; }

    private:
        ImageLoader* image_loader = nullptr;
        GLuint textureID = 0;
        ImVec2 size;
        ImVec2 uv0, uv1;

        // Button
        std::string m_Text;
        ImVec4 m_BgColor = ImVec4(0, 0, 0, 0); // Transparent (no override)
        ImVec4 m_TextColor = ImVec4(1, 1, 1, 1); // White text
        std::function<void()> onClick;
      

        // Image relative
        ImVec2 m_ImageSize;          // custom size of the image
        ImVec2 m_ImageOffset;        // position relative to button
        ImVec4 m_ImageTint = ImVec4(1,1,1,1); // RGBA
        bool scale_enable = true;

    };
}
