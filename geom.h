#ifndef YUENYEUNG_GEOM_H
#define YUENYEUNG_GEOM_H

#include "base.h"
#include "math.h"

#include <cmath>

struct ray {
  v3f32 origin;
  v3f32 dir;
};

struct sphere {
  v3f32 center;
  f32   radius;
};

inline v3f32 at(ray r, f32 t) {
  return r.origin + t * r.dir;
}

inline f32 hit(sphere s, ray r) {
  v3f32 oc = s.center - r.origin;
  f32   a  = lensq(r.dir);
  f32   h  = dot(r.dir, oc);
  f32   c  = lensq(oc) - s.radius * s.radius;
  f32   d  = h * h - a * c;

  if (d < 0)
    return -1;
  return (h - std::sqrt(d)) / a;
}

inline v3f32 color(ray r) {
  sphere s = {{0, 0, -1}, 0.5f};
  f32    t = hit(s, r);
  if (t > 0) {
    v3f32 n = unit(at(r, t) - s.center);
    return 0.5f * v3f32{n.x + 1, n.y + 1, n.z + 1};
  }

  v3f32 unit_dir = unit(r.dir);
  f32   blend    = 0.5f * (unit_dir.y + 1);

  return (1 - blend) * v3f32{1, 1, 1} + blend * v3f32{0.5f, 0.7f, 1};
}

#endif
