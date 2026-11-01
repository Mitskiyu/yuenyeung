#ifndef YUENYEUNG_MATH_H
#define YUENYEUNG_MATH_H

#include "base.h"
#include <cmath>

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

inline f32 sqlen(v3f32 v) {
  return dot(v, v);
}

inline f32 len(v3f32 v) {
  return sqrtf(sqlen(v));
}

inline v3f32 unit(v3f32 v) {
  return v / len(v);
}

#endif
