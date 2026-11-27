#include "render.h"

#include "base.h"
#include "color.h"
#include "geom.h"
#include "material.h"
#include "math.h"
#include "random.h"

#include <cmath>
#include <cstdio>
#include <print>

static v3f32 sample_sq() {
  return v3f32{rand_f32() - 0.5f, rand_f32() - 0.5f, 0};
}

static v3f32 sample_defocus_disk(const camera &cam) {
  v3f32 p = rand_v3f32_in_disk_unit();
  return cam.center + (p.x * cam.defocus_disk_x) + (p.y * cam.defocus_disk_y);
}

static ray get_ray(const camera &cam, i32 x, i32 y) {
  v3f32 offset    = sample_sq();
  v3f32 px_sample = cam.px_origin +
                    ((static_cast<f32>(x) + offset.x) * cam.px_dt_x) +
                    ((static_cast<f32>(y) + offset.y) * cam.px_dt_y);

  v3f32 ray_origin =
      (cam.defocus_ang <= 0) ? cam.center : sample_defocus_disk(cam);
  v3f32 ray_dir = px_sample - ray_origin;
  return ray{ray_origin, ray_dir};
}

static v3f32 ray_color(const scene &world, ray r, i32 depth) {
  if (depth <= 0)
    return v3f32{};

  constexpr f32 t_min = 0.001f;
  if (auto h = isect(world, r, {t_min, inf})) {
    material mat = world.materials[h->mat_idx];
    if (auto b = scatter(mat, r.dir, h->normal, h->outside))
      return b->atten * ray_color(world, ray{h->p, b->dir}, depth - 1);

    return {0, 0, 0};
  }

  v3f32 unit_dir = unit(r.dir);
  f32   t        = 0.5f * (unit_dir.y + 1);

  return (1 - t) * v3f32{1, 1, 1} + t * v3f32{0.5f, 0.7f, 1};
}

camera make_camera(const camera_settings &s) {
  i32 img_height = static_cast<i32>(s.img_width / s.aspect_ratio);
  img_height     = (img_height < 1) ? 1 : img_height;

  f32 theta     = deg_to_rad(s.vfov);
  f32 h         = std::tan(theta / 2);
  f32 vp_height = 2 * h * s.focus_dist;
  f32 vp_width  = vp_height * static_cast<f32>(s.img_width) / img_height;

  v3f32 w = unit(s.center - s.target);
  v3f32 u = unit(cross(s.up, w));
  v3f32 v = cross(w, u);

  v3f32 vp_x = vp_width * u;
  v3f32 vp_y = vp_height * -v;

  v3f32 px_dt_x = vp_x / static_cast<f32>(s.img_width);
  v3f32 px_dt_y = vp_y / static_cast<f32>(img_height);

  v3f32 vp_ul     = s.center - (s.focus_dist * w) - vp_x / 2 - vp_y / 2;
  v3f32 px_origin = vp_ul + 0.5f * (px_dt_x + px_dt_y);

  f32 defocus_rad = s.focus_dist * std::tan(deg_to_rad(s.defocus_ang / 2));

  return camera{
      .img_width        = s.img_width,
      .img_height       = img_height,
      .max_depth        = s.max_depth,
      .samples_per_px   = s.samples_per_px,
      .px_samples_scale = 1.0f / s.samples_per_px,
      .center           = s.center,
      .px_origin        = px_origin,
      .px_dt_x          = px_dt_x,
      .px_dt_y          = px_dt_y,
      .defocus_ang      = s.defocus_ang,
      .defocus_disk_x   = u * defocus_rad,
      .defocus_disk_y   = v * defocus_rad,
  };
}

void render(const scene &world, const camera &cam) {
  std::println("P3\n{} {}\n255", cam.img_width, cam.img_height);
  for (i32 y{}; y < cam.img_height; y++) {
    std::print(stderr, "\rScanlines remaining: {} ", cam.img_height - y);

    for (i32 x{}; x < cam.img_width; x++) {
      v3f32 px_color{0, 0, 0};
      for (i32 sample{}; sample < cam.samples_per_px; sample++) {
        ray r = get_ray(cam, x, y);
        px_color += ray_color(world, r, cam.max_depth);
      }

      std::println("{}", write_color(cam.px_samples_scale * px_color));
    }
  }

  std::println(stderr, "\rDone                       ");
}
