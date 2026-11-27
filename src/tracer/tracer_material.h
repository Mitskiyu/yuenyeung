#ifndef YUENYEUNG_TRACER_MATERIAL_H
#define YUENYEUNG_TRACER_MATERIAL_H

#include "base/base_math.h"
#include "base/base_random.h"
#include "base/base_types.h"

#include <algorithm>
#include <cmath>
#include <optional>

namespace pt {

enum class material_kind : u8 { matte, metal, dielectric };

struct material {
  v3f32 albedo;
  f32   fuzz;
  f32   ior;

  material_kind kind;
};

inline material make_matte(v3f32 albedo) {
  return {.albedo = albedo, .kind = material_kind::matte};
}

inline material make_metal(v3f32 albedo, f32 fuzz) {
  return {.albedo = albedo, .fuzz = fuzz, .kind = material_kind::metal};
}

inline material make_dielectric(f32 ior) {
  return {.ior = ior, .kind = material_kind::dielectric};
}

struct bounce {
  v3f32 dir;
  v3f32 atten;
};

inline f32 reflectance(f32 cosine, f32 eta_ratio) {
  f32 f0 = (1 - eta_ratio) / (1 + eta_ratio);
  f0     = f0 * f0;

  f32 t = 1 - cosine;
  return f0 + (1 - f0) * t * t * t * t * t;
}

inline std::optional<bounce> scatter(material mat, v3f32 inc_dir, v3f32 normal,
                                     bool outside) {
  switch (mat.kind) {
  case material_kind::matte: {
    constexpr f32 threshold = 1e-8f;
    v3f32         dir       = normal + rand_v3f32_unit();
    if (lensq(dir) < threshold)
      dir = normal;

    v3f32 atten = mat.albedo;
    return bounce{dir, atten};
  }

  case material_kind::metal: {
    v3f32 dir   = reflect(inc_dir, normal);
    dir         = unit(dir) + (mat.fuzz * rand_v3f32_unit());
    v3f32 atten = mat.albedo;

    if (dot(dir, normal) <= 0)
      break;

    return bounce{dir, atten};
  }

  case material_kind::dielectric: {
    v3f32 atten     = {1, 1, 1};
    f32   eta_ratio = outside ? (1 / mat.ior) : mat.ior;

    v3f32 dir       = unit(inc_dir);
    f32   cos_theta = std::min<f32>(dot(-dir, normal), 1);
    f32   sin_theta = std::sqrt(1 - cos_theta * cos_theta);

    bool tir = eta_ratio * sin_theta > 1;
    if (tir || reflectance(cos_theta, eta_ratio) > rand_f32())
      dir = reflect(dir, normal);
    else
      dir = refract(dir, normal, eta_ratio);

    return bounce{dir, atten};
  }
  }

  return std::nullopt;
}
} // namespace pt

#endif
