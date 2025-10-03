#include "indra_toolkit/modules/resource_management/image/ImageLoader.h"
#include "indra_toolkit/modules/resource_management/ResourceManager.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace indra_toolkit;

ImageLoader::~ImageLoader()
{
    OnShutdown();
}

void ImageLoader::OnShutdown()
{
    for (auto& kv : _textures) {
        glDeleteTextures(1, &kv.second);
    }
    _textures.clear();
}
GLuint ImageLoader::LoadTexture(const std::string& relativePath, int* out_width, int* out_height)
{
    // full path from resource manager
    std::string absPath = resource_manager->ResolvePath(relativePath);

    // cache check (use absPath as key)
    auto it = _textures.find(absPath);
    if (it != _textures.end()) {
        if (out_width) *out_width = 0;
        if (out_height) *out_height = 0;
        return it->second;
    }

    GLuint texID = 0;
    if (absPath.size() >= 4 &&
        (absPath.substr(absPath.size()-4) == ".xpm" ||
         absPath.substr(absPath.size()-4) == ".XPM"))
    {
        texID = LoadTextureFromXPMFile(absPath, out_width, out_height);
    }
    else {
        texID = LoadTextureFromFile(absPath, out_width, out_height);
    }

    if (texID != 0) {
        _textures[absPath] = texID;
    }
    return texID;
}


GLuint ImageLoader::LoadTextureFromFile(const std::string& pathToImage, int* out_width, int* out_height)
{
    int width, height, channels;
    unsigned char* data = stbi_load(pathToImage.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load image: " << pathToImage << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);

    if (out_width) *out_width = width;
    if (out_height) *out_height = height;

    return texture;
}
GLuint indra_toolkit::ImageLoader::LoadTextureFromXPMFile(const std::string& pathToImage, int* out_width, int* out_height)
{
    std::ifstream file(pathToImage);
    if (!file.is_open()) {
        std::cerr << "Failed to open XPM file: " << pathToImage << std::endl;
        return 0;
    }

    std::string line;
    // Skip lines until we reach the first quoted line (header)
    while (std::getline(file, line)) {
        size_t q = line.find('"');
        if (q != std::string::npos)
            break;
    }

    // Parse header: width, height, numColors, charsPerPixel
    int width, height, numColors, cpp;
    {
        size_t q1 = line.find('"');
        size_t q2 = line.rfind('"');
        std::string header = line.substr(q1 + 1, q2 - q1 - 1);
        if (!header.empty() && header.back() == ',') header.pop_back();

        std::istringstream iss(header);
        iss >> width >> height >> numColors >> cpp;
        
        // Debug output to verify parsing
        // std::cout << "XPM Header: " << width << "x" << height 
        //           << ", colors: " << numColors << ", cpp: " << cpp << std::endl;
    }

    if (out_width) *out_width = width;
    if (out_height) *out_height = height;

    // Parse color table
    std::map<std::string, std::array<unsigned char,4>> colorTable;
    for (int i = 0; i < numColors; i++) {
        std::getline(file, line);
        size_t q1 = line.find('"');
        size_t q2 = line.rfind('"');
        if (q1 == std::string::npos || q2 == std::string::npos) {
            continue; // Skip malformed lines
        }
        
        std::string entry = line.substr(q1 + 1, q2 - q1 - 1);
        if (!entry.empty() && entry.back() == ',') entry.pop_back();

        // Extract the key - use exactly cpp characters
        std::string key = entry.substr(0, cpp);

        // Find the color specification - look for " c " or " g " etc.
        size_t cpos = entry.find(" c ");
        if (cpos == std::string::npos) {
            cpos = entry.find(" g "); // try gray
        }
        if (cpos == std::string::npos) {
            cpos = entry.find(" m "); // try mono
        }
        
        if (cpos == std::string::npos) {
            std::cerr << "Warning: Could not find color spec in: " << entry << std::endl;
            continue;
        }

        std::string colorField = entry.substr(cpos + 3); // Skip " c "
        std::istringstream cs(colorField);
        std::string colorStr;
        cs >> colorStr;

        // Remove any trailing commas from colorStr
        if (!colorStr.empty() && colorStr.back() == ',') {
            colorStr.pop_back();
        }

        std::array<unsigned char,4> rgba = {255,255,255,255}; // default white

        if (colorStr == "None") {
            rgba = {0,0,0,0}; // transparent
        } else if (!colorStr.empty() && colorStr[0] == '#') {
            unsigned int hexValue;
            // Handle both 6-digit and 3-digit hex colors
            if (colorStr.length() == 7) { // #RRGGBB
                sscanf(colorStr.c_str(), "#%06x", &hexValue);
                rgba[0] = (hexValue >> 16) & 0xFF; // R
                rgba[1] = (hexValue >> 8) & 0xFF;  // G  
                rgba[2] = hexValue & 0xFF;         // B
                rgba[3] = 255;                     // A
            } else if (colorStr.length() == 4) { // #RGB
                sscanf(colorStr.c_str(), "#%03x", &hexValue);
                rgba[0] = ((hexValue >> 8) & 0xF) * 17; // R
                rgba[1] = ((hexValue >> 4) & 0xF) * 17; // G
                rgba[2] = (hexValue & 0xF) * 17;        // B
                rgba[3] = 255;                          // A
            }
        } else {
            // simple named colors fallback
            if (colorStr == "black") rgba = {0,0,0,255};
            else if (colorStr == "white") rgba = {255,255,255,255};
            else if (colorStr == "green") rgba = {0,255,0,255};
            else if (colorStr == "red") rgba = {255,0,0,255};
            else if (colorStr == "blue") rgba = {0,0,255,255};
            else {
                std::cerr << "Unknown color: " << colorStr << std::endl;
            }
        }

        colorTable[key] = rgba;
        // std::cout << "Color table: '" << key << "' -> " 
        //           << (int)rgba[0] << "," << (int)rgba[1] << "," 
        //           << (int)rgba[2] << "," << (int)rgba[3] << std::endl;
    }

    // Parse pixels
    std::vector<unsigned char> pixels(width * height * 4, 0);
    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        size_t q1 = line.find('"');
        size_t q2 = line.rfind('"');
        if (q1 == std::string::npos || q2 == std::string::npos) {
            continue; // Skip malformed lines
        }
        
        std::string row = line.substr(q1 + 1, q2 - q1 - 1);
        if (!row.empty() && row.back() == ',') row.pop_back();

        // Verify row length matches expected
        if (row.length() < (size_t)(width * cpp)) {
            std::cerr << "Row " << y << " too short: expected " << (width * cpp) 
                      << " chars, got " << row.length() << std::endl;
            continue;
        }

        for (int x = 0; x < width; x++) {
            std::string key = row.substr(x * cpp, cpp);
            auto it = colorTable.find(key);
            std::array<unsigned char,4> rgba = {0,0,0,0}; // default transparent black
            
            if (it != colorTable.end()) {
                rgba = it->second;
            } else {
                std::cerr << "Unknown color key: '" << key << "' at " << x << "," << y << std::endl;
            }

            int idx = (y * width + x) * 4;
            pixels[idx+0] = rgba[0];
            pixels[idx+1] = rgba[1];
            pixels[idx+2] = rgba[2];
            pixels[idx+3] = rgba[3];
        }
    }

    file.close();

    // Debug: Check first few pixels
    // std::cout << "First pixel: " << (int)pixels[0] << "," << (int)pixels[1] 
    //           << "," << (int)pixels[2] << "," << (int)pixels[3] << std::endl;

    // Upload to OpenGL
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    return texture;
}