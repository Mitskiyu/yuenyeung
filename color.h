#ifndef YUENYEUNG_COLOR_H
#define YUENYEUNG_COLOR_H

#include "base.h"
#include "math.h"

#include <cmath>
#include <format>
#include <string>

inline f32 linear_to_gamma(f32 c) {
  if (c > 0)
    return std::sqrt(c);

  return 0;
}

inline v3f32 linear_to_gamma(v3f32 c) {
  c.x = linear_to_gamma(c.x);
  c.y = linear_to_gamma(c.y);
  c.z = linear_to_gamma(c.z);

  return c;
}

inline std::string write_color(v3f32 color) {
  color = linear_to_gamma(color);
  f32 r = color.x;
  f32 g = color.y;
  f32 b = color.z;

  constexpr interval intensity{0, 0.999f};

  i32 rb = static_cast<i32>(256 * clamp(intensity, r));
  i32 gb = static_cast<i32>(256 * clamp(intensity, g));
  i32 bb = static_cast<i32>(256 * clamp(intensity, b));

  return std::format("{} {} {}", rb, gb, bb);
}

#endif
