#ifndef YUENYEUNG_COLOR_H
#define YUENYEUNG_COLOR_H

#include "base.h"
#include "math.h"

#include <format>
#include <string>

inline std::string write_color(v3f32 color) {
  f32 r = color.x;
  f32 g = color.y;
  f32 b = color.z;

  i32 rb = static_cast<i32>(255.999f * r);
  i32 gb = static_cast<i32>(255.999f * g);
  i32 bb = static_cast<i32>(255.999f * b);

  return std::format("{} {} {}", rb, gb, bb);
}

#endif
