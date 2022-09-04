#pragma once

#include <cassert>
#include <string>

#include "szyfr_cezara.h"

// Vigenere cypher
static std::string VigenereCypher(std::string_view src, std::string_view key) {
  std::string result(src.size(), '\0');

  for (size_t i = 0; i < src.size(); i++) {
    char c = src[i];
    assert(c >= 'a' && c <= 'z');
    assert(key[i % key.size()] >= 'a' && key[i % key.size()] <= 'z');
    char k = key[i % key.size()] - 'a';
    // `+1` because 'a' should shift by one not 0
    result[i] = CesarCypherShift(c, k) + 1;
  }

  return result;
}

// Decipher vigenere cypher
static std::string DecipherVigenereCypher(std::string_view cypher,
                                          std::string_view key) {
  std::string result(cypher.size(), '\0');

  for (size_t i = 0; i < cypher.size(); i++) {
    char c = cypher[i];
    char k = key[i % key.size()];
    // `-1` because 'a' shifts by one so we need to take this into the account
    result[i] = CesarCypherShift(c, kAlphabetSize - (k - 'a')) - 1;
  }

  return result;
}