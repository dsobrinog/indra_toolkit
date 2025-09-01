#include "indra_toolkit/widgets/ImageWidget.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static bool EndsWith(const std::string& str, const std::string& suffix)
{
    if (suffix.size() > str.size()) return false;
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin(),
        [](char a, char b){ return tolower(a) == tolower(b); });
}

indra_toolkit::ImageWidget::ImageWidget(const std::string& pathToImage, const ImVec2& size)
{
    SetSize(size);

    int width, height;

    if(EndsWith(pathToImage, ".xpm"))
    {
        textureID = LoadTextureFromXPMFile(pathToImage, &width, &height); 
    }
    else textureID = LoadTextureFromFile(pathToImage, &width, &height);

    if(GetSize().x != width || GetSize().y != height)
    {
        std::cout << "Loaded an image that has a different image size than the widget size it was used in" << std::endl;
    }
}

GLuint indra_toolkit::ImageWidget::LoadTextureFromFile(const std::string& pathToImage, int* out_width, int* out_height)
{
    int width, height, channels;
    unsigned char* data = stbi_load(pathToImage.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cout << "Failed to load image!" << std::endl;
        return -1;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters (repeat / filtering)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the image to GPU
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data); // free CPU-side image memory

    if (out_width) *out_width = width;
    if (out_height) *out_height = height;

    return texture;
}

GLuint indra_toolkit::ImageWidget::LoadTextureFromXPMFile(const std::string& pathToImage, int* out_width, int* out_height)
{
    std::ifstream file(pathToImage);
    if (!file.is_open()) {
        std::cerr << "Failed to open XPM file: " << pathToImage << std::endl;
        return 0;
    }

    std::string line;
    // Skip lines until we reach the header
    while (std::getline(file, line)) {
        if (!line.empty() && line[0] == '\"')
            break;
    }

    // Parse header: width, height, numColors, charsPerPixel
    int width, height, numColors, cpp;
    {
        std::istringstream iss(line.substr(1)); // skip first quote
        iss >> width >> height >> numColors >> cpp;
    }

    if (out_width) *out_width = width;
    if (out_height) *out_height = height;

    // Parse color table
    std::map<std::string, unsigned int> colorTable;
    for (int i = 0; i < numColors; i++) {
        std::getline(file, line);
        size_t q1 = line.find('"');
        size_t q2 = line.rfind('"');
        std::string entry = line.substr(q1 + 1, q2 - q1 - 1);

        std::string key = entry.substr(0, cpp);
        size_t pos = entry.find("c ");
        std::string colorStr = entry.substr(pos + 2);

        unsigned int rgba = 0xFFFFFFFF; // default white
        if (colorStr == "None") {
            rgba = 0x00000000; // transparent
        } else if (colorStr[0] == '#') {
            unsigned int r, g, b;
            if (colorStr.length() == 7) { // #RRGGBB
                sscanf(colorStr.c_str(), "#%02x%02x%02x", &r, &g, &b);
                rgba = (r << 0) | (g << 8) | (b << 16) | (0xFF << 24);
            }
        }
        colorTable[key] = rgba;
    }

    // Parse pixels
    std::vector<unsigned int> pixels(width * height, 0);
    for (int y = 0; y < height; y++) {
        std::getline(file, line);
        size_t q1 = line.find('"');
        size_t q2 = line.rfind('"');
        std::string row = line.substr(q1 + 1, q2 - q1 - 1);

        for (int x = 0; x < width; x++) {
            std::string key = row.substr(x * cpp, cpp);
            pixels[y * width + x] = colorTable[key];
        }
    }

    file.close();

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

indra_toolkit::ImageWidget::~ImageWidget()
{
    glDeleteTextures(1, &textureID);
}

void indra_toolkit::ImageWidget::Draw()
{
    if (!IsEnabled()) return;

    ImGui::Image(((void*)(intptr_t)textureID), GetPixelSize()); 
}
