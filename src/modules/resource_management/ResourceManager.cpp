#include "indra_toolkit/modules/resource_management/ResourceManager.h"
#include "indra_toolkit/ToolApplication.h"

#include <iostream>

using namespace indra_toolkit;

ResourceManager::ResourceManager(ToolApplication* app_, ToolModules module_identity)
    : Module(app_, module_identity)
{
    // Default resource folder relative to executable
    res_root = std::filesystem::current_path() / "res";

    // Initialize loaders
    fontLoader = std::make_unique<FontLoader>(app_);
    imageLoader = std::make_unique<ImageLoader>();

    // _soundLoader = std::make_unique<SoundLoader>(app, module_identity);

    fontLoader->SetResourceManager(this);
    imageLoader->SetResourceManager(this);

    std::cout << "ResourceManager initialized, root res folder: " 
              << res_root << std::endl;
}

void ResourceManager::OnShutdown()
{
    if (fontLoader) { fontLoader->OnShutdown(); }
    if (imageLoader) { imageLoader->OnShutdown(); }
    // if (_soundLoader) { _soundLoader->OnShutdown(); }
}

void ResourceManager::SetResourceRoot(const std::string& path)
{
    res_root = std::filesystem::absolute(path);
    std::cout << "Resource root set to: " << res_root << std::endl;
}

std::string ResourceManager::ResolvePath(const std::string& relative_path) const
{
    std::filesystem::path full_path = res_root / relative_path;
    return full_path.string();
}

