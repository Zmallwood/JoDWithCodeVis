/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class ImageBank {
  public:
    ImageBank();
    
    ~ImageBank();
    
    GLuint GetImage(int imageNameHash);
    
    GLuint GetImage(std::string_view imageName);
    
    void CreateBlankImage(std::string uniqueImageName);
    
    Size GetImageDimensions(int imageNameHash);
    
  private:
    void LoadImages();
    
    GLuint LoadSingleImage(std::string_view absoluteFilePath);
    
    const std::string k_relativeImagesPath{"Resources/Images/"};
    std::map<int, GLuint> m_images;
};
}
