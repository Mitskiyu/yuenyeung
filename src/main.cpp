#include "geom.h"
#include "material.h"
#include "render.h"

#include "render.cpp"

int main() {
  camera cam = make_camera({
      .aspect_ratio   = 16.0f / 9.0f,
      .img_width      = 1024,
      .max_depth      = 50,
      .samples_per_px = 100,
      .defocus_ang    = 10,
      .focus_dist     = 3.4f,
      .vfov           = 20,
      .up             = {0, 1, 0},
      .center         = {-2, 2, 1},
      .target         = {0, 0, -1},
  });

  scene world;
  world.materials = {
      make_matte({0.8f, 0.8f, 0.0f}),
      make_matte({0.1f, 0.2f, 0.5f}),
      make_dielectric(1.5f),
      make_dielectric(1 / 1.5f),
      make_metal({0.8f, 0.6f, 0.2f}, 1),
  };

  world.spheres = {
      {{0, -100.5f, -1}, 100, 0}, {{0, 0, -1.2f}, 0.5f, 1},
      {{-1, 0, -1}, 0.5f, 2},     {{-1, 0, -1}, 0.4f, 3},
      {{1, 0, -1}, 0.5f, 4},
  };

  render(world, cam);
}
