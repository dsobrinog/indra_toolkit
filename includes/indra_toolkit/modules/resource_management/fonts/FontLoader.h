#pragma once
#include <imgui.h>

#include "indra_toolkit/Module.h"
#include <string>
#include <unordered_map>

namespace indra_toolkit
{
    class ResourceManager;

    class FontLoader
    {
    public:
        FontLoader(ToolApplication* app){};
        ~FontLoader() { OnShutdown(); }

        void OnShutdown(){};

        // Load a font from file and store it by name
        ImFont* LoadFont(const std::string& name, const std::string& relative_path, float size);

        // Get a loaded font by name
        ImFont* GetFont(const std::string& name);

        // After loading fonts, rebuild the font atlas
        inline bool RebuildFontAlias()
        {
            return ImGui::GetIO().Fonts->Build();
        }

        // Apply a font for ImGui usage
        inline void UseFont(const std::string& name)
        {
            ImFont* font = GetFont(name);
            if (font)
                ImGui::PushFont(font);
        }

        inline void EndFont()
        {
            ImGui::PopFont();
        }

        inline void SetResourceManager(ResourceManager* rm){
            resource_manager = rm;
        }

    private:
        ResourceManager* resource_manager = nullptr;
        std::unordered_map<std::string, ImFont*> _fonts;
    };
}