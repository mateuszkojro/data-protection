#pragma once

#include <map>

#include <string>

static double Coincidence(std::string_view text) {

  std::map<char, int> char_counts;
  for (char c : text) {
    char_counts[c]++;
  }

  double sum = 0;
  for(auto [c, count] : char_counts) {
    sum += count * (count - 1);
  }

  return sum / (text.size() * (text.size() - 1));
}