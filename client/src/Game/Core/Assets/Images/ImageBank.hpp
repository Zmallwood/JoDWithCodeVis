/*
 * Copyright 2024 Andreas Åkerberg
 */

#pragma once

namespace JoD {
class ImageBank {
  public:
    ImageBank();
    
    ~ImageBank();
    
    GLuint GetImage(int imageNameHash) const;
    
    GLuint GetImage(std::string_view imageName) const;
    
    void CreateBlankImage(std::string uniqueImageName);
    
    Size GetImageDimensions(int imageNameHash) const;
    
  private:
    void LoadImages();
    
    GLuint LoadSingleImage(std::string_view absoluteFilePath) const;
    
    std::map<int, GLuint> m_images;
    
    const std::string k_relativeImagesPath{"Resources/Images/"};
};
}
