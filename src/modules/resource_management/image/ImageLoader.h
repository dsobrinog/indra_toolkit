#pragma once

#include "imgui.h"
#include "indra_toolkit/Module.h"

#include <GL/gl.h> 

#include <string>
#include <unordered_map>

// #include <glad/glad.h>   // or GLEW


// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>

namespace indra_toolkit
{
    class ImageLoader : public Module
    {
    public:
        ImageLoader(ToolApplication* app, const ToolModules& module_identity) : Module(app, module_identity) {}
        ~ImageLoader() { OnShutdown(); }

            
        virtual void OnShutdown() override;

        // PNG
        ImTextureID LoadTexture(const std::string& path);
        void FreeTexture(const std::string& path);

        // XPM
        ImTextureID LoadTextureXPM(const char** xpm);
    
    private:
        GLuint LoadXPM(const char** xpm);

        //std::unordered_map<std::string, GLuint> _textures; // store texture IDs
    };
}
