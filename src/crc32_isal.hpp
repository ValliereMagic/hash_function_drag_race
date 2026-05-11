#pragma once
#include <cstring>

#include "byte_ranges.hpp"
extern "C" {
#include <isa-l.h>
}

struct CRC32C {
  template <ByteRange InputRange>
  std::array<std::uint8_t, 32> digest_message(InputRange&& byte_range) {
    auto hash =
        crc32_iscsi(const_cast<unsigned char*>(std::ranges::data(byte_range)),
                    std::ranges::size(byte_range), 0);

    std::array<std::uint8_t, 32> seed{};
    std::memcpy(seed.data(), &hash, sizeof(hash));
    return seed;
  }
};
