
#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <cryptopp/secblock.h>
#include <string>

class Crypto {

 public:
  Crypto() = default;

  ~Crypto() = default;

  void clear();

  void set_salt(const CryptoPP::SecByteBlock &salt);

  void set_saltsize(const std::size_t saltsize);

  void set_keysize(const std::size_t keysize);

  void set_ivsize(const unsigned int);

  void set_hmac_iterations(const unsigned int);

  CryptoPP::SecByteBlock get_salt() const;

  std::size_t get_saltsize() const;

  std::size_t get_keysize() const;

  std::size_t get_ivsize() const;

  unsigned int get_hmac_iterations() const;

  template<typename Archive>
  void serialize(Archive &ar);

 private:
  CryptoPP::SecByteBlock salt_m;
  std::string encryption_m, prng_m;
  unsigned int hmac_iterations_m;
  std::size_t saltsize_m, keysize_m, ivsize_m;
};

#endif // CRYPTO_HPP
