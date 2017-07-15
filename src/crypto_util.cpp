

#include "../include/crypto_util.hpp"
#include "../include/AES_RNG.h"
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

// encrypts account information using AES in GCM mode
const std::string CryptoUtilities::AES_GCM_Encrypt(const std::string &plaintext,
                                                   CryptoPP::SecByteBlock &key,
                                                   CryptoPP::SecByteBlock &iv) {

  std::string ciphertext, encoded;

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
    encoded.clear();
    // exit(1);
  }
  // DEBUG: pretty print a std::string
  encoded.clear();
  CryptoPP::StringSource(
      ciphertext, true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
  std::cout << "cipher text: " << encoded << std::endl;

  return encoded;
}

const std::string
CryptoUtilities::AES_GCM_Decrypt(const std::string &ciphertext,
                                 CryptoPP::SecByteBlock &key,
                                 CryptoPP::SecByteBlock &iv) {
  std::string recovered;

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

// derives PBKDF2 hash for given message using SHA-512
const CryptoPP::SecByteBlock
CryptoUtilities::GetPBKDF2(unsigned int iterations,
                           CryptoPP::SecByteBlock &salt, std::size_t keysize,
                           const std::string &message) {

  // time in seconds to perform derivation
  double timeinSec = 0; // if 0, total iterations will be run

  // byte buffer to receive the derived password
  CryptoPP::SecByteBlock derived(keysize);

  // declare PBKDF2-SHA512 variable
  CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA512> pbkdf2;

  // Derive key using above parameters
  pbkdf2.DeriveKey(derived, derived.size(), 0, (const byte *)message.data(),
                   message.size(), salt, salt.size(), iterations, timeinSec);

  std::string result = CryptoUtilities::SecByteBlockToString(derived);
  std::cout << "Derived pbkdf2: " << result << std::endl;

  return (derived); // return as a secbyte buffer
}

// AES-256 pseudorandom number generator
const CryptoPP::SecByteBlock
CryptoUtilities::Get_AES_PseudoRNG(const size_t &saltlen) {
  // fetches random seed from the OS
  CryptoPP::SecByteBlock seed(32); // 32 byte
  CryptoPP::OS_GenerateRandomBlock(false, seed, seed.size());

  // compute pseudorandom number
  AES_RNG prng(seed, seed.size());

  CryptoPP::SecByteBlock randomval(saltlen);
  prng.GenerateBlock(randomval, randomval.size());

  return (randomval);
}

const std::string
CryptoUtilities::SecByteBlockToString(CryptoPP::SecByteBlock &buffer) {
  std::string result;
  // convert secbyteblock to std string and print key
  result.clear();
  CryptoPP::StringSource(
      buffer, buffer.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));

  return (result);
}

const CryptoPP::SecByteBlock
CryptoUtilities::StringToSecByteBlock(const std::string &buffer) {
  CryptoPP::SecByteBlock result((const byte *)buffer.data(), buffer.size());
  return (result);
}
