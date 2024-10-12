/*
 * Copyright 2024 Andreas Åkerberg
 */

namespace JoD {
Point3F Point3F::Translate(float dx, float dy, float dz) {
    return {x + dx, y + dy, z + dz};
}
}
