#ifndef MATH_VEC_H
#define MATH_VEC_H

#include <array>
#include <cmath>

namespace math {
template <class T, std::size_t N> class Vec {
public:
  using value_type = T;
  using size_type = std::size_t;

  Vec() {}

  template <class... Values> Vec(const Values &... v) : values_{v...} {}

  Vec(std::array<T, N> vals) : values_(vals) {}

  constexpr size_type size() const { return N; }

  T &operator[](const size_type idx) { return values_[idx]; }
  T operator[](const size_type idx) const { return values_[idx]; }

  Vec operator-() const {
    auto res = Vec();
    for (auto i = 0u; i < N; ++i) {
      res[i] = -values_[i];
    }
    return res;
  }

  Vec operator*(const Vec &b) const {
    auto res = Vec();
    for (auto i = 0u; i < N; ++i) {
      res[i] = values_[i] * b[i];
    }
    return res;
  }

  Vec operator/(const Vec &b) const {
    auto res = Vec();
    for (auto i = 0u; i < N; ++i) {
      res[i] = values_[i] / b[i];
    }
    return res;
  }

  Vec operator+(const Vec &b) const {
    auto res = Vec();
    for (auto i = 0u; i < N; ++i) {
      res[i] = values_[i] + b[i];
    }
    return res;
  }

  Vec operator-(const Vec &b) const {
    auto res = Vec();
    for (auto i = 0u; i < N; ++i) {
      res[i] = values_[i] - b[i];
    }
    return res;
  }

  Vec Normalized() {
    auto len2 = T{0};
    for (auto i = 0u; i < N; ++i) {
      len2 += values_[i] * values_[i];
    }
    return std::sqrt(len2);
  }

  T *Data() { return values_.data(); }
  const T *Data() const { return values_.data(); }

private:
  std::array<T, N> values_;
};

template <class T>
Vec<T, 3> CrossProduct(const Vec<T, 3> &v1, const Vec<T, 3> &v2) {
  return Vec<T, 3>(v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2],
                   v1[0] * v2[1] - v1[1] * v2[0]);
}

template <class T, std::size_t N>
T DotProduct(const Vec<T, N> &v1, const Vec<T, N> &v2) {
  auto res = T{0};
  for (auto i = 0u; i < N; ++i) {
    res += v1[i] * v2[i];
  }
  return res;
}
}

#endif
