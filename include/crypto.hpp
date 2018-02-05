
#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>

class Crypto {

public:
  Crypto() = default;
  void clear();

  void set_saltsize(const std::size_t saltsize);
  void set_keysize(const std::size_t keysize);
  void set_ivsize(const unsigned int);
  void set_hmac_iterations(const unsigned int);
  std::size_t get_saltsize() const;
  std::size_t get_keysize() const;
  std::size_t get_ivsize() const;
  unsigned int get_hmac_iterations() const;

  template <typename Archive> void serialize(Archive &ar);

private:
  std::string encryption_m, prng_m;
  unsigned int hmac_iterations_m;
  std::size_t saltsize_m, keysize_m, ivsize_m;
};

#endif // CRYPTO_HPP
