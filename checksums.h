#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

// TODO(mkojro) wtf is going on?
// NOTE(mkojro) Krotki tekst powoduje wieksze prawdopodobienstwo kolizji
uint32_t Adler32(const std::vector<uint32_t>& data) {
  constexpr uint32_t kModAdler = UINT32_MAX / 2;

  uint32_t a = 1, b = 0;
  size_t index;

  for (index = 0; index < data.size(); ++index) {
    a = (a + data[index]) % kModAdler;
    b = (b + a) % kModAdler;
  }

  return (b << 16) | a;
}

uint64_t DJB(const std::vector<uint64_t>& str) {
  uint64_t hash = 5381;

  for (auto c : str) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}
