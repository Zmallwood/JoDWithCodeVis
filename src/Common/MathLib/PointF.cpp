#include "PointF.hpp"

namespace JoD {
PointF PointF::Translate(float dx, float dy) const {
    return {x + dx, y + dy};
}
}
