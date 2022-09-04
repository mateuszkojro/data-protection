#pragma once

#include <map>
#include <string_view>
#include <cmath>
int AddNWDs(std::map<size_t, uint64_t>& out, uint64_t number) {
  for (int i = 1; i <= sqrt(number); i++) {
    if (number % i == 0) {
      if (number / i == i)
        out[i]++;
      else {
        out[i]++;
        out[number / i]++;
      }
    }
  }
}

// TODO(mkojro) Test this one!
std::map<size_t, uint64_t> BuildFrequencyTable(std::string_view text) {
  std::map<size_t, uint64_t> results;

  const size_t kMaxWindowSize = 6;

  for (size_t window_size = 2; window_size < kMaxWindowSize; window_size++) {
    for (size_t template_window_start_offset = 0;
         template_window_start_offset < text.size() - window_size;
         template_window_start_offset++) {
      std::string_view template_window =
          text.substr(template_window_start_offset, window_size);

      for (size_t comparing_window_offset =
               template_window_start_offset + window_size;
           comparing_window_offset < text.size(); comparing_window_offset++) {
        std::string_view moving_window =
            text.substr(template_window_start_offset, window_size);

        if (template_window == moving_window) {
          results[comparing_window_offset - template_window_start_offset]++;
        }
      }
    }
  }
  return results;
}
