#include "base.h"
#include "color.h"
#include "geom.h"
#include "math.h"

#include <cstdio>
#include <print>

static v3f32 ray_color(const scene &world, ray r);

int main() {
  f32 aspect_ratio = 16.0f / 9.0f;
  i32 img_width    = 1024;
  i32 img_height   = static_cast<i32>(img_width / aspect_ratio);
  img_height       = (img_height < 1) ? 1 : img_height;

  scene world;
  world.spheres.push_back({{0, 0, -1}, 0.5f});
  world.spheres.push_back({{0, -100.5f, -1}, 100});

  f32 focal_length    = 1;
  f32 viewport_height = 2;
  f32 viewport_width =
      viewport_height * static_cast<f32>(img_width) / img_height;
  v3f32 camera_center = {0, 0, 0};

  v3f32 viewport_x = {viewport_width, 0, 0};
  v3f32 viewport_y = {0, -viewport_height, 0};

  v3f32 pixel_dt_x = viewport_x / static_cast<f32>(img_width);
  v3f32 pixel_dt_y = viewport_y / static_cast<f32>(img_height);

  v3f32 viewport_ul  = camera_center - v3f32{0, 0, focal_length} -
                       viewport_x / 2 - viewport_y / 2;
  v3f32 pixel_origin = viewport_ul + 0.5f * (pixel_dt_x + pixel_dt_y);

  std::println("P3\n{} {}\n255", img_width, img_height);
  for (i32 y{}; y < img_height; y++) {
    std::print(stderr, "\rScanlines remaining: {} ", img_height - y);

    for (i32 x{}; x < img_width; x++) {
      v3f32 pixel_center = pixel_origin + (static_cast<f32>(x) * pixel_dt_x) +
                           (static_cast<f32>(y) * pixel_dt_y);
      v3f32 ray_dir      = pixel_center - camera_center;
      ray   r            = {camera_center, ray_dir};

      v3f32 pixel_color = ray_color(world, r);
      std::println("{}", write_color(pixel_color));
    }
  }

  std::println(stderr, "\rDone                       ");
}

static v3f32 ray_color(const scene &world, ray r) {
  if (auto h = isect(world, r, 0, inf))
    return 0.5f * (h->normal + v3f32{1, 1, 1});

  v3f32 unit_dir = unit(r.dir);
  f32   t        = 0.5f * (unit_dir.y + 1);

  return (1 - t) * v3f32{1, 1, 1} + t * v3f32{0.5f, 0.7f, 1};
}
