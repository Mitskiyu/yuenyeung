#include "base.h"
#include "geom.h"
#include "material.h"
#include "math.h"
#include "render.h"

#include "render.cpp"

#include <cmath>

int main() {
  f32    vfov           = 90;
  f32    aspect_ratio   = 16.0f / 9.0f;
  i32    img_width      = 1024;
  i32    max_depth      = 50;
  i32    samples_per_px = 100;
  camera cam =
      make_camera(vfov, aspect_ratio, img_width, max_depth, samples_per_px);

  scene world;

  world.materials = {
      make_matte({0, 0, 1}),
      make_matte({1, 0, 0}),
  };

  f32 r         = std::cos(pi / 4);
  world.spheres = {
      {{-r, 0, -1}, r, 0},
      {{r, 0, -1}, r, 1},
  };

  // world.materials = {
  //     make_matte({0.8f, 0.8f, 0.0f}),
  //     make_matte({0.1f, 0.2f, 0.5f}),
  //     make_dielectric(1.5f),
  //     make_dielectric(1 / 1.5f),
  //     make_metal({0.8f, 0.6f, 0.2f}, 1),
  // };
  //
  // world.spheres = {
  //     {{0, -100.5f, -1}, 100, 0}, {{0, 0, -1.2f}, 0.5f, 1},
  //     {{-1, 0, -1}, 0.5f, 2},     {{-1, 0, -1}, 0.4f, 3},
  //     {{1, 0, -1}, 0.5f, 4},
  // };

  render(world, cam);
}
