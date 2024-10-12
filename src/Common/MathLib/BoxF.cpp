/*
 * Copyright 2024 Andreas Åkerberg
 */

#include "BoxF.hpp"

namespace JoD {
GLBoxF BoxF::ToGLBoxF() const {
    return {x * 2 - 1.0f, 1.0f - y * 2, width * 2, height * 2};
}

PointF BoxF::GetCenter() const {
    return {x + width/2, y + height/2};
}
}
