#pragma once
#include <bitset>
#include <cmath>
#include <vector>

uint64_t ModPower(uint64_t base, uint64_t exponent, uint64_t modulo) {
  constexpr uint64_t kExponentBitCount = 64;

  std::vector<uint64_t> powers_to_the_power_of_two;
  uint64_t current_power = base;
  for(uint64_t power_of_two = 1; power_of_two < exponent; power_of_two *= 2) {
    powers_to_the_power_of_two.push_back(current_power * base);
  }

  std::bitset<kExponentBitCount> exponent_bits(exponent);
  uint64_t result = 1;
  for (size_t bit = 0 ; bit < kExponentBitCount; bit++) {
    result *= (exponent_bits[bit] * powers_to_the_power_of_two[bit]) % modulo;
  }

  return result;
}

