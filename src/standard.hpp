#pragma once

#include <cstring>

#include "byte_ranges.hpp"
struct Standard {
  template <ByteRange InputRange>
  std::array<std::uint8_t, 32> digest_message(InputRange&& range) {
    std::string_view hash_view{
        reinterpret_cast<const char*>(std::ranges::data(range)),
        std::ranges::size(range)};

    std::size_t hash = std::hash<std::string_view>{}(hash_view);

    std::array<std::uint8_t, 32> hash_output{};
    std::memcpy(hash_output.data(), &hash, sizeof(std::size_t));
    return hash_output;
  }
};
