

#ifndef CRYPTO_UTIL_HPP
#define CRYPTO_UTIL_HPP

#include "amphora_mediator.hpp"
#include <cryptopp/secblock.h>
#include <string>

class CryptoUtilities {

public:
    CryptoUtilities(const AmphoraMediator &m);

    ~CryptoUtilities();

    // TODO p1-6 use SecByteBlock only and neve std::string

    std::string AES_GCM_Encrypt(const std::string &plaintext,
                                CryptoPP::SecByteBlock &key,
                                CryptoPP::SecByteBlock &iv);

    std::string AES_GCM_Decrypt(const std::string &ciphertext,
                                CryptoPP::SecByteBlock &key,
                                CryptoPP::SecByteBlock &iv);

    // std::string AES_GCM_Encrypt(const std::string &plaintext,
    //                             const std::string &keystr,
    //                             const std::string &ivstr);
    // std::string AES_GCM_Decrypt(const std::string &ciphertext,
    //                             const std::string &key, const std::string &iv);
    // std::string PBKDF2(unsigned int iterations, const std::string &salt,
    //                    std::size_t keysize, const std::string &message);
    // std::string AES_PRNG(const size_t &saltlen);
    CryptoPP::SecByteBlock PBKDF2(unsigned int iterations,
                                  CryptoPP::SecByteBlock &salt,
                                  std::size_t keysize,
                                  const std::string &message);

    CryptoPP::SecByteBlock AES_PRNG(const size_t &saltlen);

    std::string SecByteBlockToString(CryptoPP::SecByteBlock &buffer);

    CryptoPP::SecByteBlock StringToSecByteBlock(const std::string &buffer);

private:
    AmphoraMediator mediator_m;
};

#endif // CRYPTO_UTIL_HPP
