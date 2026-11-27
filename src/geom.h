#ifndef YUENYEUNG_GEOM_H
#define YUENYEUNG_GEOM_H

#include "base.h"
#include "math.h"

#include <cmath>
#include <optional>
#include <vector>

struct ray {
  v3f32 origin;
  v3f32 dir;
};

struct sphere {
  v3f32 center;
  f32   radius;
};

struct hit {
  v3f32 normal;
  v3f32 p;
  f32   t;
  bool  outside;
};

struct scene {
  std::vector<sphere> spheres;
};

inline v3f32 at(ray r, f32 t) {
  return r.origin + t * r.dir;
}

inline std::optional<hit> isect(sphere s, ray r, interval t_range) {
  v3f32 oc = s.center - r.origin;
  f32   a  = lensq(r.dir);
  f32   h  = dot(r.dir, oc);
  f32   c  = lensq(oc) - s.radius * s.radius;
  f32   d  = h * h - a * c;

  if (d < 0)
    return std::nullopt;

  f32 sqrtd = std::sqrt(d);
  f32 root  = (h - sqrtd) / a;
  if (!surrounds(t_range, root)) {
    root = (h + sqrtd) / a;

    if (!surrounds(t_range, root))
      return std::nullopt;
  }

  v3f32 p       = at(r, root);
  v3f32 outward = (p - s.center) / s.radius;
  bool  outside = dot(r.dir, outward) < 0;

  return hit{outside ? outward : -outward, p, root, outside};
}

inline std::optional<hit> isect(const scene &s, ray r, interval t_range) {
  std::optional<hit> best    = std::nullopt;
  f32                closest = t_range.max;

  for (auto sph : s.spheres) {
    if (auto h = isect(sph, r, {t_range.min, closest})) {
      best    = h;
      closest = h->t;
    }
  }

  return best;
}

#endif
