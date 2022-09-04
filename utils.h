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
  uint64_t result = 1;
  for(size_t i = 0; i < exponent; i++) {
    result *= base;
  }
  return result;
}

uint64_t Pow2(uint64_t exponent) {
  return 1ull << exponent;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& iterable) {
  os << "{ ";
  for (const auto& elem : iterable) {
    os << elem << ',';
  }
  os << " }";
  return os;
}


static bool IsValidChar(char c) { return c >= 'a' && c <= 'z'; }
