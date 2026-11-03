#include "base.h"
#include "color.h"
#include "geom.h"
#include "math.h"

#include <cstdio>
#include <print>

int main() {
  f32 aspect_ratio = 16.0f / 9.0f;
  i32 img_width    = 1024;
  i32 img_height   = static_cast<i32>(img_width / aspect_ratio);
  img_height       = (img_height < 1) ? 1 : img_height;

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

      v3f32 pixel_color = color(r);
      std::println("{}", write_color(pixel_color));
    }
  }

  std::println(stderr, "\rDone                       ");
}
