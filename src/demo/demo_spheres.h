#ifndef YUENYEUNG_DEMO_SPHERES_H
#define YUENYEUNG_DEMO_SPHERES_H

#include "base/base_math.h"
#include "base/base_random.h"
#include "base/base_types.h"
#include "pt/pt_material.h"
#include "pt/pt_render.h"
#include "pt/pt_scene.h"

namespace demo {

struct setup {
  pt::scene       world;
  pt::camera_desc desc;
};

inline setup spheres() {
  setup s;

  pt::add_sphere(s.world, {0, -1000, 0}, 1000,
                 pt::make_matte({0.5f, 0.5f, 0.5f}));

  for (i32 a = -11; a < 11; a++) {
    for (i32 b = -11; b < 11; b++) {
      f32   choose_mat = rand_f32();
      v3f32 center     = {a + 0.9f * rand_f32(), 0.2f, b + 0.9f * rand_f32()};

      if (len(center - v3f32{4, 0.2f, 0}) <= 0.9f)
        continue;

      if (choose_mat < 0.8f) {
        v3f32 albedo = rand_v3f32(0.0f, 1.0f) * rand_v3f32(0.0f, 1.0f);
        pt::add_sphere(s.world, center, 0.2f, pt::make_matte(albedo));
      } else if (choose_mat < 0.95f) {
        v3f32 albedo = rand_v3f32(0.5f, 1.0f);
        f32   fuzz   = rand_f32(0.0f, 0.5f);
        pt::add_sphere(s.world, center, 0.2f, pt::make_metal(albedo, fuzz));
      } else {
        pt::add_sphere(s.world, center, 0.2f, pt::make_dielectric(1.5f));
      }
    }
  }

  pt::add_sphere(s.world, {0, 1, 0}, 1, pt::make_dielectric(1.5f));
  pt::add_sphere(s.world, {-4, 1, 0}, 1, pt::make_matte({0.4f, 0.2f, 0.1f}));
  pt::add_sphere(s.world, {4, 1, 0}, 1, pt::make_metal({0.7f, 0.6f, 0.5f}, 0));

  s.desc = {
      .defocus_ang = 0.6f,
      .focus_dist  = 10,
      .vfov        = 20,
      .up          = {0, 1, 0},
      .center      = {13, 2, 3},
      .target      = {0, 0, 0},
  };

  return s;
}
} // namespace demo

#endif
