#include "base/base_math.h"
#include "base/base_os.h"
#include "base/base_random.h"
#include "base/base_types.h"
#include "pt/pt_color.h"
#include "pt/pt_geom.h"
#include "pt/pt_material.h"
#include "pt/pt_render.h"

#include "pt/pt_render.cpp"
#if _WIN32
#include "win32/win32_base.cpp"
#endif

#include <cstdio>
#include <print>
#include <vector>

int main() {
  pt::scene world;

  auto add = [&](v3f32 center, f32 radius, pt::material mat) {
    world.materials.push_back(mat);
    u16 mat_idx = static_cast<u16>(world.materials.size() - 1);
    world.spheres.push_back({center, radius, mat_idx});
  };

  add({0, -1000, 0}, 1000, pt::make_matte({0.5f, 0.5f, 0.5f}));

  for (i32 a = -11; a < 11; a++) {
    for (i32 b = -11; b < 11; b++) {
      f32   choose_mat = rand_f32();
      v3f32 center     = {a + 0.9f * rand_f32(), 0.2f, b + 0.9f * rand_f32()};

      if (len(center - v3f32{4, 0.2f, 0}) <= 0.9f)
        continue;

      if (choose_mat < 0.8f) {
        v3f32 albedo = rand_v3f32(0.0f, 1.0f) * rand_v3f32(0.0f, 1.0f);
        add(center, 0.2f, pt::make_matte(albedo));
      } else if (choose_mat < 0.95f) {
        v3f32 albedo = rand_v3f32(0.5f, 1.0f);
        f32   fuzz   = rand_f32(0.0f, 0.5f);
        add(center, 0.2f, pt::make_metal(albedo, fuzz));
      } else {
        add(center, 0.2f, pt::make_dielectric(1.5f));
      }
    }
  }

  add({0, 1, 0}, 1, pt::make_dielectric(1.5f));
  add({-4, 1, 0}, 1, pt::make_matte({0.4f, 0.2f, 0.1f}));
  add({4, 1, 0}, 1, pt::make_metal({0.7f, 0.6f, 0.5f}, 0));

  pt::camera cam = pt::make_camera({
      .aspect_ratio   = 16.0f / 9.0f,
      .img_width      = 1200,
      .max_depth      = 50,
      .samples_per_px = 500,
      .defocus_ang    = 0.6f,
      .focus_dist     = 10,
      .vfov           = 20,
      .up             = {0, 1, 0},
      .center         = {13, 2, 3},
      .target         = {0, 0, 0},
  });

  u64 before = time_now_us();

  std::vector<v3f32> pixels = pt::render(world, cam);

  f64 total = static_cast<f64>(time_now_us() - before) / 1e6;
  std::println(stderr, "{:.3f}s", total);
  pt::write_ppm(pixels, cam.img_width, cam.img_height);
}
