

#include "crypto.hpp"
// #include "cereal/archives/json.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/types/string.hpp"

void Crypto::clear() {
  saltsize_m = 0;
  keysize_m = 0;
  ivsize_m = 0;
}

void Crypto::set_salt(const CryptoPP::SecByteBlock &salt) { salt_m = salt; }

void Crypto::set_saltsize(const std::size_t saltsize) { saltsize_m = saltsize; }

void Crypto::set_keysize(const std::size_t keysize) { keysize_m = keysize; }

void Crypto::set_ivsize(const unsigned int ivsize) { ivsize_m = ivsize; }

void Crypto::set_hmac_iterations(const unsigned int iterations) {
  hmac_iterations_m = iterations;
}

std::size_t Crypto::get_saltsize() const { return saltsize_m; }

std::size_t Crypto::get_keysize() const { return keysize_m; }

std::size_t Crypto::get_ivsize() const { return ivsize_m; }

unsigned int Crypto::get_hmac_iterations() const { return hmac_iterations_m; }

template <typename Archive> inline void Crypto::serialize(Archive &ar) {
  ar(saltsize_m, keysize_m, ivsize_m, hmac_iterations_m);
}

// template void
// Crypto::serialize<cereal::JSONOutputArchive>(cereal::JSONOutputArchive &);
// template void
// Crypto::serialize<cereal::JSONInputArchive>(cereal::JSONInputArchive &);

template void
Crypto::serialize<cereal::XMLOutputArchive>(cereal::XMLOutputArchive &);
template void
Crypto::serialize<cereal::XMLInputArchive>(cereal::XMLInputArchive &);
