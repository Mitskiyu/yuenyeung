#ifndef YUENYEUNG_MATERIAL_H
#define YUENYEUNG_MATERIAL_H

#include "base.h"
#include "math.h"
#include "random.h"

#include <optional>

enum class material_kind : u8 { matte, metal };

struct material {
  material_kind kind;
  v3f32         albedo;
};

struct bounce {
  v3f32 dir;
  v3f32 atten;
};

inline std::optional<bounce> scatter(material mat, v3f32 inc_dir,
                                     v3f32 normal) {
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
    v3f32 atten = mat.albedo;

    return bounce{dir, atten};
  }
  }

  return std::nullopt;
}

#endif
