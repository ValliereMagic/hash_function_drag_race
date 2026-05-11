#pragma once

#include <stdexcept>

#include "byte_ranges.hpp"

extern "C" {
#include <openssl/evp.h>
}

struct OpenSSLEVP {
  EVP_MD_CTX* md_context;
  const EVP_MD* md_type;

  OpenSSLEVP(const EVP_MD* type) : md_type(type) {
    if ((md_context = EVP_MD_CTX_new()) == nullptr) {
      throw std::runtime_error{"Unable to allocate EVP MD Context."};
    }
  }
  ~OpenSSLEVP() { EVP_MD_CTX_free(md_context); }

  template <ByteRange InputRange>
  std::array<std::uint8_t, 32> digest_message(InputRange&& byte_range) {
    if (EVP_DigestInit_ex(md_context, md_type, nullptr) != 1) {
      throw std::runtime_error{"Unable to initialize EVP context."};
    }

    if (EVP_DigestUpdate(md_context, std::ranges::data(byte_range),
                         std::ranges::size(byte_range)) != 1) {
      throw std::runtime_error{"Unable to digest passed range."};
    }
    std::array<std::uint8_t, 32> resultant_digest{};

    if (EVP_DigestFinal_ex(md_context, resultant_digest.data(), nullptr) != 1) {
      throw std::runtime_error{"Unable to copy result out of md_context."};
    }

    return resultant_digest;
  }
};
