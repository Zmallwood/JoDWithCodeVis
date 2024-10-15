#include "Trigonometry.hpp"

namespace JoD {
float SinDegrees(float angleDegrees) {
    return sinf(angleDegrees * static_cast<float>(M_PI) / 180.0f);
}

float CosDegrees(float angleDegrees) {
    return cosf(angleDegrees * static_cast<float>(M_PI) / 180.0f);
}
}
