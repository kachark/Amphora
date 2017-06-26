

#ifndef CRYPTO_UTIL_HPP
#define CRYPTO_UTIL_HPP

#include <string>

class CryptoUtilities {

public:
  std::string Encrypt(std::string customkey);
  std::string Decrypt(std::string ciphertext);
  std::string GetPBKDF2(const std::string &message);
  std::string GetSalt(const size_t &saltlen);

};

#endif // CRYPTO_UTIL_HPP
