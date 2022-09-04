#pragma once

#include <iostream>
#include <map>
#include <random>
#include <string>

#include "checksums.h"
#include "utils.h"

constexpr size_t kAlphabetSize = 26;

const std::vector<uint64_t> kAlphabet{
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

//
std::vector<uint64_t> ReverseDJB(uint64_t hash) {
  constexpr size_t kResultSize = 8;
  std::vector<uint64_t> result(kResultSize);
  for (int i = 0; i < kResultSize; i++) {
    result.push_back('a' +
                     (hash / Pow(kAlphabet.size(), i)) % kAlphabet.size());
  }
  return result;
}

uint64_t Random(uint64_t min, uint64_t max) {
  uint64_t diff = max - min;
  return min + (rand() % diff);
}

std::vector<uint64_t> MakeRandomString(size_t length) {
  std::vector<uint64_t> string(length);
  for (unsigned long long& i : string) {
    i = kAlphabet[Random(0, kAlphabetSize)];
  }
  return string;
}

std::map<uint64_t, std::vector<uint64_t>> CreateRainbowTable(
    size_t height, size_t width, size_t password_length) {
  std::map<uint64_t, std::vector<uint64_t>> rainbow_table;
  for (size_t y = 0; y < height; y++) {
    auto original_password = MakeRandomString(password_length);
    uint64_t hash = DJB(original_password);
    for (size_t x = 1; x < width; x++) {
      hash = DJB(ReverseDJB(hash));
    }
    rainbow_table[hash] = original_password;
  }
  return rainbow_table;
}

template <class T>
void PrintIterable(T iterable, std::ostream& ostream = std::cout) {
  std::cout << "{ ";
  for (const auto& elem : iterable) {
    ostream << elem << ',';
  }
  std::cout << " }";
}

void TryBreak(uint64_t hash, size_t width, size_t height,
              const std::map<uint64_t, std::vector<uint64_t>>& table) {
  for (size_t y = 0; y < height; y++) {
    hash = DJB(ReverseDJB(hash));
    for (size_t x = 1; x < width; x++) {
      if (auto hash_string_iter = table.find(hash);
          hash_string_iter != table.end()) {
        std::vector<uint64_t> found_string = hash_string_iter->second;
        for (size_t i = 0; i < width - x; i++) {
          found_string = ReverseDJB(DJB(found_string));
        }
        PrintIterable(found_string);
      }
    }
  }
}