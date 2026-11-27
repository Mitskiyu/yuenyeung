#ifndef YUENYEUNG_PT_SCENE_H
#define YUENYEUNG_PT_SCENE_H

#include "base/base_math.h"
#include "base/base_types.h"
#include "pt/pt_geom.h"
#include "pt/pt_material.h"

#include <optional>
#include <vector>

namespace pt {

struct scene {
  std::vector<sphere>   spheres;
  std::vector<material> materials;
};

inline void add_sphere(scene &s, v3f32 center, f32 radius, material mat) {
  s.materials.push_back(mat);
  s.spheres.push_back(
      {center, radius, static_cast<u16>(s.materials.size() - 1)});
}

inline std::optional<hit> raycast(const scene &s, ray r, interval t_range) {
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
} // namespace pt

#endif
