#ifndef YUENYEUNG_RENDER_H
#define YUENYEUNG_RENDER_H

#include "base.h"
#include "geom.h"
#include "math.h"

struct camera {
  f32   aspect_ratio;
  i32   img_width;
  i32   max_depth;
  i32   samples_per_px;
  v3f32 center;

  // computed
  i32   img_height;
  f32   px_samples_scale;
  v3f32 px_dt_x, px_dt_y;
  v3f32 px_origin;
};

camera make_camera(f32 aspect_ratio, i32 img_width, i32 max_depth,
                   i32 samples_per_px);
void   render(const scene &world, const camera &cam);

#endif
