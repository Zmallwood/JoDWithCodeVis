/*
 * Copyright 2024 Andreas Åkerberg
 */

namespace JoD {
Point2 Point2::Translate(int dx, int dy) const {
    return {x + dx, y + dy};
}
}
