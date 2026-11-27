#ifndef YUENYEUNG_RENDER_H
#define YUENYEUNG_RENDER_H

#include "base.h"
#include "geom.h"
#include "math.h"

struct camera_settings {
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

camera make_camera(f32 aspect_ratio, i32 img_width, i32 max_depth,
                   i32 samples_per_px);
void   render(const scene &world, const camera &cam);

#endif
