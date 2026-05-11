#pragma once

#include <cstring>

#include "byte_ranges.hpp"

struct DJB2 {
  template <ByteRange InputRange>
  std::array<std::uint8_t, 32> digest_message(InputRange&& range) {
    std::size_t hash = 5381;

    for (auto&& byte : range) {
      hash = ((hash << 5) + hash) + byte;
    }

    std::array<std::uint8_t, 32> hash_output{};
    std::memcpy(hash_output.data(), &hash, sizeof(std::size_t));

    return hash_output;
  }
};
