#ifndef YUENYEUNG_RAY_H
#define YUENYEUNG_RAY_H

#include "base.h"
#include "math.h"

struct ray {
  v3f32 origin;
  v3f32 dir;
};

inline v3f32 at(ray r, f32 t) {
  return r.origin + t * r.dir;
}

inline v3f32 color(ray r) {
  v3f32 unit_dir = unit(r.dir);
  f32   t        = 0.5f * (unit_dir.y + 1.0f);

  return (1.0f - t) * v3f32{1.0f, 1.0f, 1.0f} + t * v3f32{0.5f, 0.7f, 1.0f};
}

#endif
