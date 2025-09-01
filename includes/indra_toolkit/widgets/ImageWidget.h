#pragma once

#include "imgui.h"
#include "indra_toolkit/Widget.h"
#include <string>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

namespace indra_toolkit
{
    // Basic Image widget
    class ImageWidget : public Widget
    {
    public:
        ImageWidget(const std::string& pathToImage, const ImVec2& size);
        virtual ~ImageWidget();

        virtual void Draw() override;

    protected:
        GLuint LoadTextureFromFile(const std::string& pathToImage, int* out_width, int* out_height);
        GLuint LoadTextureFromXPMFile(const std::string& pathToImage, int* out_width, int* out_height);

    private:
        GLuint textureID;
    };
}