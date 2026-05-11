#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

#include "crc32_isal.hpp"
#include "djb2.hpp"
#include "hardware_sha256.hpp"
#include "standard.hpp"
#include "xxhash_struct.hpp"

static std::vector<std::uint8_t> read_file() {
  std::ifstream file{"./random_bytes", std::ios::binary | std::ios::ate};
  if (!file.good()) {
    throw std::runtime_error(
        "Failed to open random bytes source file. Does it exist?");
  }
  std::streamsize file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  std::vector<std::uint8_t> buffer;
  buffer.resize(file_size);
  file.read(reinterpret_cast<char*>(buffer.data()), file_size);
  if (!file.good()) {
    throw std::runtime_error("Failed to read in file bytes.");
  }
  return buffer;
}

template <ByteRange InputRange>
static std::vector<std::basic_string_view<std::uint8_t>> chunkify_file(
    InputRange&& buffer) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<std::size_t> dist(6, 15);

  std::vector<std::basic_string_view<std::uint8_t>> chunks;

  std::size_t offset = 0;
  while (offset < std::ranges::size(buffer)) {
    std::size_t len = dist(rng);
    len = std::min(len, std::ranges::size(buffer) - offset);

    chunks.emplace_back(reinterpret_cast<const std::uint8_t*>(
                            std::ranges::data(buffer) + offset),
                        len);

    offset += len;
  }

  return chunks;
}

template <typename T>
inline void do_not_optimize(T const& value) {
  asm volatile("" : : "r,m"(value) : "memory");
}

template <typename Digester, typename InputRange>
  requires std::ranges::input_range<InputRange> &&
           HasDigest<Digester, std::ranges::range_value_t<InputRange>>
static void time_run(InputRange&& chunks, Digester&& digester,
                     std::string_view algorithm) {
  auto begin = std::chrono::steady_clock::now();

  for (auto&& chunk : chunks) {
    do_not_optimize(digester.digest_message(chunk));
  }

  auto end = std::chrono::steady_clock::now();
  std::cout << algorithm << " took "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                     begin)
            << '\n';
}

int main(void) {
  auto buffer = read_file();
  auto symbol_chunks = chunkify_file(buffer);

  OpenSSLEVP sha_context{EVP_sha256()};
  OpenSSLEVP sha1_context{EVP_sha1()};
  OpenSSLEVP MD5_context{EVP_md5()};
  CRC32C CRC_context;
  XXHASH xxhash_context;
  DJB2 djb2_context;
  Standard standard_context;

  time_run(symbol_chunks, sha_context, "SHA256");
  time_run(symbol_chunks, sha1_context, "SHA1");
  time_run(symbol_chunks, MD5_context, "MD5");
  time_run(symbol_chunks, CRC_context, "CRC32C Intel ISA-L");
  time_run(symbol_chunks, xxhash_context, "XXHASH");
  time_run(symbol_chunks, djb2_context, "DJB2");
  time_run(symbol_chunks, standard_context, "std::hash");

  return EXIT_SUCCESS;
}
