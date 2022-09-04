#pragma once

#include <cstddef>
#include <cstdint>

#include "utils.h"

static constexpr uint64_t modulus = 23;
static constexpr uint64_t base = 5;
// TODO(mkojro) implement whole exchange thingy
uint64_t APowBModC(uint64_t a, uint64_t b, uint64_t c) {
  return Pow(a,b) % c;
}

