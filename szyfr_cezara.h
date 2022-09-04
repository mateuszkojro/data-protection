#pragma once

#include <string>

static constexpr int kAlphabetSize = 26;

static char CesarCypherShift(char c, int shift) {
  return (c + shift - 'a') % kAlphabetSize + 'a';
}

// Cesars cypher
static std::string CesarsCypher(std::string_view src, int key) {
  std::string dst(src.size(), '\0');
  int idx = 0;
  for (char c : src) {
    dst[idx++] = CesarCypherShift(c, key);
  }
  return dst;
}

// Decipher cesars cypher
static std::string DecipherCesarsCypher(std::string_view cypher, int key) {
  return CesarsCypher(cypher, kAlphabetSize - key);
}
