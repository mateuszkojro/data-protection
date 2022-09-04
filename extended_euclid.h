#pragma once

#include <cstdint>

/// Does (a,b) = (b, new_b)
void SwapAndAssign(uint64_t& a, uint64_t& b, uint64_t new_b) {
  uint64_t tmp_a = a;
  a = b;
  b = new_b;
}

/// Znajduje najwiekszy wspolny dzielnik
/// From: https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm#Pseudocode
/// \return NWD(a,b)
uint64_t ExtendedEuclid(uint64_t a, uint64_t b) {
  uint64_t old_r = a;
  uint64_t r = b;
  uint64_t old_s = 1;
  uint64_t s = 0;
  uint64_t old_t = 0;
  uint64_t t = 1;

  while (r != 0) {
    uint64_t quotient = old_r / r;  // Dzielenie calkowite
    /*
     * (old_r, r) := (r, old_r − quotient × r)
     * (old_s, s) := (s, old_s − quotient × s)
     * (old_t, t) := (t, old_t − quotient × t)
     */
    SwapAndAssign(old_r, r, old_r - quotient * r);
    SwapAndAssign(old_s, s, old_s - quotient * s);
    SwapAndAssign(old_t, t, old_t - quotient * t);
  }
  return old_r;
}