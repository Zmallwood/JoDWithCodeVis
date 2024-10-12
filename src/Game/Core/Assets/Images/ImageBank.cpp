/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "ImageBank.hpp"
#include "Common/FileUtilities.hpp"
#include "Game/Core/Graphics/Graphics.hpp"

namespace JoD {
ImageBank::ImageBank() {
    LoadImages();
}

ImageBank::~ImageBank() {
    for (const auto &image : m_images)
        glDeleteTextures(1, &image.second);
}

GLuint ImageBank::GetImage(int imageNameHash) {
    for (auto image : m_images)
        if (image.first == imageNameHash)
            return image.second;
    return -1;
}

GLuint ImageBank::GetImage(std::string_view imageName) {
    return GetImage(Hash(imageName));
}

void ImageBank::CreateBlankImage(std::string uniqueImageName) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    m_images.insert({Hash(uniqueImageName), texture_id});
}

void ImageBank::LoadImages() {
    using iterator = std::filesystem ::recursive_directory_iterator;
    auto allImagesPath =
        std::string(SDL_GetBasePath()) + k_relativeImagesPath.data();
    for (auto &entry : iterator(allImagesPath)) {
        auto absolutePath = entry.path().string();
        std::replace(absolutePath.begin(), absolutePath.end(), '\\', '/');
        if (GetFileExtension(absolutePath) != "png")
            continue;
        auto textureID = LoadSingleImage(absolutePath);
        auto imageName = GetFilenameNoExtension(absolutePath);
        auto imageNameHash = Hash(imageName);
        m_images[imageNameHash] = textureID;
    }
}

GLuint ImageBank::LoadSingleImage(std::string_view absoluteFilePath) {
    GLuint textureID;
    auto surface = IMG_Load(absoluteFilePath.data());
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    if (surface->format->BytesPerPixel == 4)
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, surface->pixels);
    else
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGB,
            GL_UNSIGNED_BYTE, surface->pixels);
    SDL_FreeSurface(surface);
    return textureID;
}

Size ImageBank::GetImageDimensions(int imageNameHash) {
    Size dim{0, 0};
    auto imageID = GetImage(imageNameHash);
    if (imageID != -1) {
        int mipLevel = 0;
        glBindTexture(GL_TEXTURE_2D, imageID);
        glGetTexLevelParameteriv(
            GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH,
            &dim.width);
        glGetTexLevelParameteriv(
            GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT,
            &dim.height);
    }
    return dim;
}
}
