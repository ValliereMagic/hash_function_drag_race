#pragma once

#include <cstring>

#include "byte_ranges.hpp"
extern "C" {
#include <xxhash.h>
}

struct XXHASH {
  template <ByteRange InputRange>
  std::array<std::uint8_t, 32> digest_message(InputRange&& byte_range) {
    auto hash = XXH3_64bits(std::ranges::data(byte_range),
                            std::ranges::size(byte_range));

    std::array<std::uint8_t, 32> seed{};
    std::memcpy(seed.data(), &hash, sizeof(hash));
    return seed;
  }
};
