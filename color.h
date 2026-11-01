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

  i32 rb = i32(255.999 * r);
  i32 gb = i32(255.999 * g);
  i32 bb = i32(255.999 * b);

  return std::format("{} {} {}", rb, gb, bb);
}

#endif
