#ifndef YUENYEUNG_RANDOM_H
#define YUENYEUNG_RANDOM_H

#include "base.h"

#include <random>

inline f32 rand_f32() {
  static std::uniform_real_distribution<f32> dist(0.0f, 1.0f);
  static std::mt19937                        gen{};
  return dist(gen);
}

inline f32 rand_f32(f32 min, f32 max) {
  return min + (max - min) * rand_f32();
}

#endif
