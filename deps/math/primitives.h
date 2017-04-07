#ifndef MATH_PRIMITIVES_H
#define MATH_PRIMITIVES_H

namespace math {
template <class T> constexpr T DegToRad(T v) { return v * T(M_PI) / T{180}; }
}

#endif
