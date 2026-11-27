#ifndef YUENYEUNG_PT_RENDER_H
#define YUENYEUNG_PT_RENDER_H

#include "base/base_math.h"
#include "base/base_types.h"
#include "pt/pt_scene.h"

#include <vector>

namespace pt {

struct camera_desc {
  f32 aspect_ratio;
  i32 img_width;
  i32 max_depth;
  i32 samples_per_px;

  f32 defocus_ang;
  f32 focus_dist;

  f32   vfov;
  v3f32 up;
  v3f32 center;
  v3f32 target;
};

struct camera {
  i32 img_width;
  i32 img_height;
  i32 max_depth;
  i32 samples_per_px;
  f32 px_samples_scale;

  v3f32 center;
  v3f32 px_origin;
  v3f32 px_dt_x, px_dt_y;

  f32   defocus_ang;
  v3f32 defocus_disk_x, defocus_disk_y;
};

camera             make_camera(const camera_desc &desc);
std::vector<v3f32> render(const scene &world, const camera &cam);
} // namespace pt

#endif
