#include "base.h"
#include "geom.h"
#include "render.h"

int main() {
  f32    aspect_ratio = 16.0f / 9.0f;
  i32    img_width    = 1024;
  camera cam          = make_camera(aspect_ratio, img_width);

  scene world;
  world.spheres.push_back({{0, 0, -1}, 0.5f});
  world.spheres.push_back({{0, -100.5f, -1}, 100});

  render(world, cam);
}
