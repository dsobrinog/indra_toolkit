#pragma once
#include "indra_toolkit/ToolApplication.h"
#include "indra_toolkit/Module.h"

#include "indra_toolkit/modules/resource_management/fonts/FontLoader.h"
#include "indra_toolkit/modules/resource_management/image/ImageLoader.h"

#include <string>
#include <memory>
#include <filesystem>

namespace indra_toolkit
{
    class ResourceManager : public Module
    {
    public:
        ResourceManager(ToolApplication* app_, ToolModules moduleIdentity_);

        virtual void OnShutdown() override;

        void SetResourceRoot(const std::string& path);
        const std::filesystem::path& GetResourcePath() const {return res_root;}
        std::string ResolvePath(const std::string& relative_path) const;

        // // Submodules access
        FontLoader* GetFontLoader() { return fontLoader.get(); }
        ImageLoader* GetImageLoader() { return imageLoader.get(); }

    private:
        std::filesystem::path res_root;

        std::unique_ptr<FontLoader> fontLoader;
        std::unique_ptr<ImageLoader> imageLoader;
    };
}
