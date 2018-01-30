

#include "crypto_util.hpp"
#include "AES_RNG.h"
#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/filters.h>
#include <cryptopp/gcm.h>
#include <cryptopp/hex.h>
#include <cryptopp/modes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/sha.h>
#include <iostream>

namespace amphora {
namespace internal {

/* AES-GCM Encryption */
// std::string CryptoUtilities::AES_GCM_Encrypt(const std::string &plaintext,
//                                              CryptoPP::SecByteBlock &key,
//                                              CryptoPP::SecByteBlock &iv) {
std::string CryptoUtilities::AES_GCM_Encrypt(const std::string &plaintext,
                                             const std::string &keystr,
                                             const std::string &ivstr) {

  std::string ciphertext, encoded;
  // convert key and iv to CryptoPP::SecByteBlock
  CryptoPP::SecByteBlock key = CryptoUtilities::StringToSecByteBlock(keystr);
  CryptoPP::SecByteBlock iv = CryptoUtilities::StringToSecByteBlock(ivstr);

  encoded.clear();
  encoded = CryptoUtilities::SecByteBlockToString(key);
  std::cout << "key: " << encoded << std::endl;

  encoded.clear();
  encoded = CryptoUtilities::SecByteBlockToString(iv);
  std::cout << "iv: " << encoded << std::endl;

  try {
    std::cout << "plain text: " << plaintext << std::endl;
    CryptoPP::GCM<CryptoPP::AES>::Encryption e;
    e.SetKeyWithIV(key, key.size(), iv, iv.size());
    // the StreamTransofrmationFilter adds padding
    // as required. GCM and CBC mode must be padded
    // to the block size of the cipher.
    CryptoPP::StringSource(plaintext, true,
                           new CryptoPP::AuthenticatedEncryptionFilter(
                               e, new CryptoPP::StringSink(ciphertext)));
  } catch (const CryptoPP::Exception &e) {
    std::cout << "Encryption Failed!" << std::endl;
    std::cerr << e.what() << std::endl;
    encoded.clear(); // if returns empty string, encryption failed
    // exit(1);
  }
  // DEBUG: pretty print a std::string
  // encode string to hex
  encoded.clear();
  CryptoPP::StringSource(
      ciphertext, true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
  std::cout << "cipher text: " << encoded << std::endl;

  return encoded;
}

/* AES-GCM Decryption */
// std::string CryptoUtilities::AES_GCM_Decrypt(const std::string &ciphertext,
//                                              CryptoPP::SecByteBlock &key,
//                                              CryptoPP::SecByteBlock &iv) {
std::string CryptoUtilities::AES_GCM_Decrypt(const std::string &ciphertext,
                                             const std::string &keystr,
                                             const std::string &ivstr) {
  std::string recovered;
  // convert key and iv to CryptoPP::SecByteBlock
  CryptoPP::SecByteBlock key = CryptoUtilities::StringToSecByteBlock(keystr);
  CryptoPP::SecByteBlock iv = CryptoUtilities::StringToSecByteBlock(ivstr);

  try {
    CryptoPP::GCM<CryptoPP::AES>::Decryption d;
    d.SetKeyWithIV(key, key.size(), iv, iv.size());
    // the StreamTransformationFilter removes padding as required
    CryptoPP::StringSource s(ciphertext, true,
                             new CryptoPP::AuthenticatedDecryptionFilter(
                                 d, new CryptoPP::StringSink(recovered)));
    std::cout << "recovered text: " << recovered << std::endl;
  } catch (const CryptoPP::Exception &e) {
    std::cout << "Decryption Failed!" << std::endl;
    std::cerr << e.what() << std::endl;
    recovered.clear();
    // exit(1);
  }

  return recovered;
}

/* PBKDF2 using SHA-512 */
// CryptoPP::SecByteBlock CryptoUtilities::GetPBKDF2(unsigned int iterations,
//                                                   CryptoPP::SecByteBlock
//                                                   &salt, std::size_t keysize,
//                                                   const std::string &message)
//                                                   {
std::string CryptoUtilities::PBKDF2(unsigned int iterations,
                                    const std::string &saltstr,
                                    std::size_t keysize,
                                    const std::string &message) {

  CryptoPP::SecByteBlock salt = StringToSecByteBlock(saltstr);
  // time in seconds to perform derivation
  // if 0, time not considered as a parameter
  double timeinSec = 0;

  // byte buffer to receive the derived password
  CryptoPP::SecByteBlock derived(keysize);

  // declare PBKDF2-SHA512 variable
  CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA512> pbkdf2;

  // Derive key using above parameters
  pbkdf2.DeriveKey(derived, derived.size(), 0x00, (const byte *)message.data(),
                   message.size(), salt, salt.size(), iterations, timeinSec);

  std::string result = CryptoUtilities::SecByteBlockToString(derived);

  // return (derived); // return as a secbyte buffer
  return result;
}

/* Pseudo-Random Number Generator */
std::string CryptoUtilities::AES_PRNG(const size_t &saltlen) {
  // fetches random seed from the OS
  CryptoPP::SecByteBlock seed(32); // 32 byte
  CryptoPP::OS_GenerateRandomBlock(false, seed, seed.size());

  // compute pseudorandom number
  AES_RNG prng(seed, seed.size());

  CryptoPP::SecByteBlock randomval(saltlen);
  prng.GenerateBlock(randomval, randomval.size());

  std::string result = SecByteBlockToString(randomval);
  // return (randomval);
  return result;
}

/* Converts CryptoPP::SecByteBlock to std::string with hex encoding */
std::string
CryptoUtilities::SecByteBlockToString(CryptoPP::SecByteBlock &buffer) {
  std::string result;
  // convert secbyteblock to std string (hex encoded)
  result.clear();
  CryptoPP::StringSource(
      buffer, buffer.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));

  return (result);
}

/* Decodes hex std::string and converts to CryptoPP::SecByteBlock */
CryptoPP::SecByteBlock
CryptoUtilities::StringToSecByteBlock(const std::string &buffer) {
  std::string decoded;
  decoded.clear();
  // decode string from hex
  CryptoPP::StringSource ss(
      buffer, true,
      new CryptoPP::HexDecoder(new CryptoPP::StringSink(decoded)));
  CryptoPP::SecByteBlock result((const byte *)decoded.data(), decoded.size());
  return (result);
}

} // namespace internal
} // namespace amphora
