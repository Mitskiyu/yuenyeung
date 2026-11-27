#ifndef YUENYEUNG_BASE_RANDOM_H
#define YUENYEUNG_BASE_RANDOM_H

#include "base/base_math.h"
#include "base/base_types.h"

#include <cmath>
#include <limits>
#include <random>

inline f32 rand_f32() {
  static std::uniform_real_distribution<f32> dist(0.0f, 1.0f);
  static std::mt19937                        gen{};
  return dist(gen);
}

inline f32 rand_f32(f32 min, f32 max) {
  return min + (max - min) * rand_f32();
}

inline v3f32 rand_v3f32() {
  return v3f32{rand_f32(), rand_f32(), rand_f32()};
}

inline v3f32 rand_v3f32(f32 min, f32 max) {
  return v3f32{rand_f32(min, max), rand_f32(min, max), rand_f32(min, max)};
}

inline v3f32 rand_v3f32_unit() {
  constexpr f32 min_lensq = std::numeric_limits<f32>::min() * 1e8f;
  while (true) {
    v3f32 v       = rand_v3f32(-1, 1);
    f32   v_lensq = lensq(v);

    if (v_lensq > min_lensq && v_lensq <= 1)
      return v / std::sqrt(v_lensq);
  }
}

inline v3f32 rand_v3f32_in_disk_unit() {
  while (true) {
    v3f32 v = v3f32(rand_f32(-1, 1), rand_f32(-1, 1), 0);
    if (lensq(v) < 1)
      return v;
  }
}

#endif
