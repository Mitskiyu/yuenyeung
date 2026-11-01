#include <cstdio>
#include <print>

#include "base.h"

int main() {
  int img_width  = 256;
  int img_height = 256;

  std::println("P3\n{} {}\n255", img_width, img_height);
  for (i32 y{}; y < img_height; y++) {
    std::print(stderr, "\rScanlines remaining: {} ", img_height - y);

    for (i32 x{}; x < img_width; x++) {
      f64 r = (f64)x / (img_width - 1);
      f64 g = (f64)y / (img_height - 1);
      f64 b = 0.0;

      i32 ir = i32(255.999 * r);
      i32 ig = i32(255.999 * g);
      i32 ib = i32(255.999 * b);

      std::println("{} {} {}", ir, ig, ib);
    }
  }

  std::println(stderr, "\rDone                       ");
}
