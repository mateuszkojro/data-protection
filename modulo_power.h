#pragma once
#include <bitset>
#include <cmath>
#include <vector>
#include "utils.h"


uint64_t ModPower(uint64_t base, uint64_t exponent, uint64_t modulo) {
  constexpr uint64_t kExponentBitCount = 64;

  std::vector<uint64_t> powers_to_the_power_of_two;
  uint64_t current_power = 0;
  for (uint64_t power_of_two = 0; current_power < exponent; power_of_two++) {
    current_power = Pow2(power_of_two);
    powers_to_the_power_of_two.push_back(Pow(base, current_power) % modulo);
  }

  std::bitset<kExponentBitCount> exponent_bits(exponent);
  uint64_t result = 1;
  for (int bit = 0; bit < kExponentBitCount; bit++) {
    if (exponent_bits[bit] == 1) {
      result = (result * powers_to_the_power_of_two[bit]) % modulo;
    }
  }

  return result;
}
