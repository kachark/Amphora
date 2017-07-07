

#ifndef CRYPTO_UTIL_HPP
#define CRYPTO_UTIL_HPP

#include <cryptopp/secblock.h>
#include <string>

class CryptoUtilities {

public:
  std::string Encrypt(const std::string &plaintext, CryptoPP::SecByteBlock &key,
                      CryptoPP::SecByteBlock &iv);
  std::string Decrypt(const std::string &ciphertext,
                      CryptoPP::SecByteBlock &key, CryptoPP::SecByteBlock &iv);
  CryptoPP::SecByteBlock GetPBKDF2(int iterations, CryptoPP::SecByteBlock &salt,
                                   std::size_t keysize,
                                   const std::string &message);
  CryptoPP::SecByteBlock GetPseudoRNG(const size_t &saltlen);
  std::string SecByteBlockToString(CryptoPP::SecByteBlock &buffer);
  CryptoPP::SecByteBlock StringToSecByteBlock(const std::string &buffer);
};

#endif // CRYPTO_UTIL_HPP
