#include "modules/resource_management/image/ImageLoader.h"
#include <unordered_map>
#include <vector>

ImTextureID indra_toolkit::ImageLoader::LoadTexture(const std::string &path)
{
    // if (_textures.find(path) != _textures.end())
    //     return (ImTextureID)(intptr_t)_textures[path];

    // int width, height, channels;
    //unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
    
    // if (!data)
    // {
    //     std::cerr << "Failed to load image: " << path << std::endl;
    //     return nullptr;
    // }

    // GLuint textureID;
    // glGenTextures(1, &textureID);
    // glBindTexture(GL_TEXTURE_2D, textureID);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexImage2D(
    //     GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
    //     GL_RGBA, GL_UNSIGNED_BYTE, data
    // );

    //stbi_image_free(data);

    // _textures[path] = textureID;
     // (ImTextureID)(intptr_t)textureID;


    return ImTextureID(1);
}
void indra_toolkit::ImageLoader::FreeTexture(const std::string &path)
{
    // auto it = _textures.find(path);
    // if (it != _textures.end())
    // {
    //     glDeleteTextures(1, &it->second);
    //     _textures.erase(it);
    // }
}



void indra_toolkit::ImageLoader::OnShutdown()
{
    // for (auto& kv : _textures)
    // {
        //     glDeleteTextures(1, &kv.second);
        // }
        // _textures.clear();
}


// XPM Format
ImTextureID indra_toolkit::ImageLoader::LoadTextureXPM(const char **xpm)
{
    GLuint tex = LoadXPM(xpm);
    // store in _textures map with a unique key if needed
    return (ImTextureID)(intptr_t)tex;
}

GLuint indra_toolkit::ImageLoader::LoadXPM(const char **xpm)
{
    int width, height, n_colors, cpp;
    sscanf(xpm[0], "%d %d %d %d", &width, &height, &cpp, &cpp); // cpp reused

    std::unordered_map<std::string, std::vector<unsigned char>> colorMap;
    for (int i = 1; i <= n_colors; ++i)
    {
        char key[5]; // assuming cpp <= 4
        char color[16];
        sscanf(xpm[i], "%s c %s", key, color);
        unsigned int r, g, b;
        if (color[0] == '#')
            sscanf(color + 1, "%02x%02x%02x", &r, &g, &b);
        else
            r = g = b = 0; // "None" or transparent

        colorMap[key] = { (unsigned char)r, (unsigned char)g, (unsigned char)b, 255 };
    }

    std::vector<unsigned char> pixels(width * height * 4);

    for (int y = 0; y < height; ++y)
    {
        const char* row = xpm[n_colors + 1 + y];
        for (int x = 0; x < width; ++x)
        {
            std::string key(row + x * cpp, cpp);
            auto& col = colorMap[key];
            int idx = (y * width + x) * 4;
            pixels[idx + 0] = col[0];
            pixels[idx + 1] = col[1];
            pixels[idx + 2] = col[2];
            pixels[idx + 3] = col[3];
        }
    }

    GLuint texID;
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texID;
}