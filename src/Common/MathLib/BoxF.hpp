#pragma once

#include "GLBoxF.hpp"

namespace JoD {
class BoxF {
  public:
    GLBoxF ToGLBoxF() const;
    
    float x{0.0f};
    float y{0.0f};
    float width{0.0f};
    float height{0.0f};
};
}
