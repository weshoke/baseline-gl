#ifndef BASELINE_DRAW_PRIMITIVES_H
#define BASELINE_DRAW_PRIMITIVES_H

#include "math/matrix3.h"
#include "math/matrix4.h"
#include "math/vec.h"

namespace baseline {
namespace draw {
using value_type = float;
using Vec2 = math::Vec<value_type, 2>;
using Vec3 = math::Vec<value_type, 3>;
using Vec4 = math::Vec<value_type, 4>;

using Matrix3 = math::Matrix3<value_type>;
using Matrix4 = math::Matrix4<value_type>;
}
}

#endif
