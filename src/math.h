#ifndef YUENYEUNG_MATH_H
#define YUENYEUNG_MATH_H

#include "base.h"

#include <cmath>
#include <limits>
#include <numbers>

inline constexpr f32 inf = std::numeric_limits<f32>::infinity();
inline constexpr f32 pi  = std::numbers::pi_v<f32>;

struct interval {
  f32 min, max;

  static const interval empty, universe;
};

inline constexpr interval interval::empty    = interval{+inf, -inf};
inline constexpr interval interval::universe = interval{-inf, +inf};

inline bool contains(interval iv, f32 x) {
  return iv.min <= x && x <= iv.max;
}

inline bool surrounds(interval iv, f32 x) {
  return iv.min < x && x < iv.max;
}

inline f32 clamp(interval iv, f32 x) {
  if (x < iv.min)
    return iv.min;
  if (x > iv.max)
    return iv.max;

  return x;
}

struct v3f32 {
  f32 x, y, z;

  v3f32 &operator+=(v3f32 b) {
    x += b.x;
    y += b.y;
    z += b.z;
    return *this;
  }

  v3f32 &operator-=(v3f32 b) {
    x -= b.x;
    y -= b.y;
    z -= b.z;
    return *this;
  }

  v3f32 &operator*=(f32 s) {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  v3f32 &operator/=(f32 s) {
    return *this *= 1.0f / s;
  }
};

inline v3f32 operator-(v3f32 v) {
  return {-v.x, -v.y, -v.z};
}

inline v3f32 operator+(v3f32 a, v3f32 b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline v3f32 operator-(v3f32 a, v3f32 b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline v3f32 operator*(v3f32 v, f32 s) {
  return {v.x * s, v.y * s, v.z * s};
}

inline v3f32 operator*(f32 s, v3f32 v) {
  return v * s;
}

inline v3f32 operator*(v3f32 a, v3f32 b) {
  return {a.x * b.x, a.y * b.y, a.z * b.z};
}

inline v3f32 operator/(v3f32 v, f32 s) {
  return {v.x / s, v.y / s, v.z / s};
}

inline f32 dot(v3f32 a, v3f32 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline v3f32 cross(v3f32 a, v3f32 b) {
  return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

inline f32 lensq(v3f32 v) {
  return dot(v, v);
}

inline f32 len(v3f32 v) {
  return std::sqrt(lensq(v));
}

inline v3f32 unit(v3f32 v) {
  return v / len(v);
}

inline f32 deg_to_rad(f32 deg) {
  return deg * pi / 180;
}

#endif
