#pragma once

#include <iostream>

// From: https://en.wikipedia.org/wiki/Lucas%E2%80%93Lehmer_primality_test
// Where p is prime 
static bool IsMerseneNumberPrime(int p) {
  uint64_t two_to_p = 1llu << p;
  uint64_t m = two_to_p - 1;
  uint64_t s = 4;
  for (size_t i = 0; i < p - 2; i++) {
    s = (s * s - 2) % m;
  }
  return s == 0;
}
