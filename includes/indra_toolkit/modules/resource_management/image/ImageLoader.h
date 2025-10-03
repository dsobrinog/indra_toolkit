#pragma once

#include "imgui.h"
#include <string>
#include <unordered_map>
#include <GL/gl.h>
#include <iostream>

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
        ImTextureID GetTextureID(GLuint& tex_id){ return (ImTextureID)(intptr_t)tex_id; }
        void SetResourceManager(ResourceManager* rm) { resource_manager = rm; }

         // Función de búsqueda rápida de ImTextureID
        bool GetTextureByName(const std::string& name, ImTextureID& out)
        {
            auto it = _textures.find(name);
            if (it != _textures.end())
            {
                out = GetTextureID(it->second);
                return true;
            }

            std::cerr << "Failed to load texture by name: " << name << std::endl;
            return false;
        }

    private:
        GLuint LoadTextureFromFile(const std::string& pathToImage, int* out_width, int* out_height);
        GLuint LoadTextureFromXPMFile(const std::string& pathToImage, int* out_width, int* out_height);

        ResourceManager* resource_manager = nullptr;
        std::unordered_map<std::string, GLuint> _textures; // cache textures
    };
}
