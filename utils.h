#pragma once

#include <cstdint>

#define MK_ASSERT_EQ(expr1, expr2, message)                           \
  do {                                                                \
    const auto& res1 = expr1;                                         \
    const auto& res2 = expr2;                                         \
    if (res1 != res2) {                                               \
      std::stringstream ss;                                           \
      ss << "Assertion failed: `" << #expr1 << "` != `" << #expr2 "`" \
         << " because `" << res1 << "` != `" << res2                  \
         << "` with message: " << message;                            \
      throw std::runtime_error(ss.str());                             \
    }                                                                 \
  } while (false);

uint64_t Pow(uint64_t base, uint64_t exponent) {
  if (exponent == 0) {
    return 1;
  }
  if (exponent == 1) {
    return base;
  }
  for (int i = 0; i < exponent; i++) {
    base *= base;
  }

  return base;
}

static bool IsValidChar(char c) { return c >= 'a' && c <= 'z'; }
