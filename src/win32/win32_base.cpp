#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "base/base_os.h"
#include "base/base_types.h"

#include <windows.h>

u64 time_now_us() {
  static u64 freq = [] {
    LARGE_INTEGER f;
    QueryPerformanceFrequency(&f);
    return static_cast<u64>(f.QuadPart);
  }();

  LARGE_INTEGER ticks{};
  QueryPerformanceCounter(&ticks);
  u64 now  = static_cast<u64>(ticks.QuadPart);
  u64 secs = now / freq;
  u64 rem  = now % freq;

  constexpr u64 us_per_sec = 1'000'000;
  return secs * us_per_sec + rem * us_per_sec / freq;
}
