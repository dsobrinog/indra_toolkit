#pragma once

#include "imgui.h"
#include <string>
#include <unordered_map>
#include <GL/gl.h>

namespace indra_toolkit
{
    class ResourceManager;
    
    class ImageLoader
    {
    public:
        ImageLoader() = default;
        ~ImageLoader();

        void OnShutdown();

        GLuint LoadTexture(const std::string& pathToImage, int* out_width = nullptr, int* out_height = nullptr);

        inline void SetResourceManager(ResourceManager* rm) { resource_manager = rm; }

    private:
        GLuint LoadTextureFromFile(const std::string& pathToImage, int* out_width, int* out_height);
        GLuint LoadTextureFromXPMFile(const std::string& pathToImage, int* out_width, int* out_height);

        ResourceManager* resource_manager = nullptr;
        std::unordered_map<std::string, GLuint> _textures; // cache textures
    };
}
