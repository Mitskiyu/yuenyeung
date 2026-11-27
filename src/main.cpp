#include "base.h"
#include "geom.h"
#include "material.h"
#include "render.h"

#include "render.cpp"

int main() {
  f32    aspect_ratio   = 16.0f / 9.0f;
  i32    img_width      = 1024;
  i32    max_depth      = 50;
  i32    samples_per_px = 100;
  camera cam = make_camera(aspect_ratio, img_width, max_depth, samples_per_px);

  scene world;

  world.materials.push_back(material{material_kind::matte, {0.8f, 0.8f, 0}});
  world.materials.push_back(material{material_kind::matte, {0.1f, 0.2f, 0.5f}});
  world.materials.push_back(material{material_kind::metal, {0.8f, 0.8f, 0.8f}});
  world.materials.push_back(material{material_kind::metal, {0.8f, 0.6f, 0.2f}});

  world.spheres.push_back({{0, -100.5f, -1}, 100, 0});
  world.spheres.push_back({{0, 0, -1.2f}, 0.5f, 1});
  world.spheres.push_back({{-1, 0, -1}, 0.5f, 2});
  world.spheres.push_back({{1, 0, -1}, 0.5f, 3});

  render(world, cam);
}
