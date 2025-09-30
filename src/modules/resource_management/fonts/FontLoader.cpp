#include "indra_toolkit/modules/resource_management/fonts/FontLoader.h"
#include "indra_toolkit/modules/resource_management/ResourceManager.h"

using namespace indra_toolkit;

ImFont* indra_toolkit::FontLoader::LoadFont(const std::string& name, const std::string& relative_path, float size)
{
    if (_fonts.find(name) != _fonts.end())
        return _fonts[name]; // already loaded

    // Ask ResourceManager to resolve the path
    std::string fullPath = resource_manager->ResolvePath(relative_path);

    ImFont* font = ImGui::GetIO().Fonts->AddFontFromFileTTF(fullPath.c_str(), size);
    if (font)
        _fonts[name] = font;

    return font;
}

ImFont* indra_toolkit::FontLoader::GetFont(const std::string& name)
{
    auto it = _fonts.find(name);
    if (it != _fonts.end())
        return it->second;
    
        return nullptr; // font not found
}
