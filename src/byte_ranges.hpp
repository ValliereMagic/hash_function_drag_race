#pragma once

#include <cstdint>
#include <ranges>

template <typename R>
concept ByteRange =
    std::ranges::input_range<R> &&
    std::convertible_to<std::ranges::range_value_t<R>, std::uint8_t>;

template <typename T, typename R>
concept HasDigest = requires(T&& digester, R&& r) {
  { digester.digest_message(r) } -> std::same_as<std::array<std::uint8_t, 32>>;
} && ByteRange<R>;
