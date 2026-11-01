#include "base.h"
#include "color.h"
#include "math.h"

#include <cstdio>
#include <print>

int main() {
  int img_width  = 256;
  int img_height = 256;

  std::println("P3\n{} {}\n255", img_width, img_height);
  for (i32 y{}; y < img_height; y++) {
    std::print(stderr, "\rScanlines remaining: {} ", img_height - y);

    for (i32 x{}; x < img_width; x++) {
      v3f32 color = {f32(x) / (img_width - 1), f32(y) / (img_height - 1), 0};
      std::println("{}", write_color(color));
    }
  }

  std::println(stderr, "\rDone                       ");
}
