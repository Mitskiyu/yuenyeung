#include "base/base_math.h"
#include "base/base_os.h"
#include "base/base_types.h"
#include "demo/demo_spheres.h"
#include "pt/pt_color.h"
#include "pt/pt_render.h"

#include "pt/pt_render.cpp"
#if _WIN32
#include "win32/win32_base.cpp"
#endif

#include <cstdio>
#include <print>
#include <vector>

int main() {
  demo::setup d         = demo::spheres();
  d.desc.aspect_ratio   = 16.0f / 9.0f;
  d.desc.img_width      = 1200;
  d.desc.max_depth      = 50;
  d.desc.samples_per_px = 500;
  pt::camera cam        = pt::make_camera(d.desc);

  u64 before = time_now_us();

  std::vector<v3f32> pixels = pt::render(d.world, cam);

  f64 total = static_cast<f64>(time_now_us() - before) / 1e6;
  std::println(stderr, "{:.3f}s", total);

  pt::write_ppm(pixels, cam.img_width, cam.img_height);
}
