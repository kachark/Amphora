

#include "crypto_util.hpp"
#include "AES_RNG.h"
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/osrng.h>
#include <cryptopp/aes.h>
#include <cryptopp/gcm.h>
#include <cryptopp/modes.h>
// #include <cryptopp/drgb.h>
#include <iostream>


// encrypts account information using AES in GCM mode
std::string CryptoUtilities::Encrypt(CryptoPP::SecByteBlock &key, CryptoPP::SecByteBlock &iv)
{

  std::string plaintext = "HELLOWORLD! GCM";
  std::string ciphertext, encoded;

  encoded.clear();
  encoded = CryptoUtilities::SecByteBlockToString(key);
  std::cout << "key: " << encoded << std::endl;

  encoded.clear();
  encoded = CryptoUtilities::SecByteBlockToString(iv);
  std::cout << "iv: " << encoded << std::endl;

  try
  {
    std::cout << "plain text: " << plaintext << std::endl;
    CryptoPP::GCM<CryptoPP::AES>::Encryption e;
    e.SetKeyWithIV(key, key.size(), iv, iv.size());
    // the StreamTransofrmationFilter adds padding
    // as required. GCM and CBC mode must be padded
    // to the block size of the cipher.
    CryptoPP::StringSource(plaintext, true,
        new CryptoPP::AuthenticatedEncryptionFilter(e, new CryptoPP::StringSink(ciphertext)));
  }
  catch(const CryptoPP::Exception& e)
  {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
  // pretty print a std::string
  encoded.clear();
  CryptoPP::StringSource(ciphertext, true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
  std::cout << "cipher text: " << encoded << std::endl;

  return ciphertext;

}


std::string CryptoUtilities::Decrypt(const std::string &ciphertext, CryptoPP::SecByteBlock &key, CryptoPP::SecByteBlock &iv)
{
  std::string recovered;

  try
  {
    CryptoPP::GCM<CryptoPP::AES>::Decryption d;
    d.SetKeyWithIV(key, key.size(), iv, iv.size());
    // the StreamTransformationFilter removes padding as required
    CryptoPP::StringSource s(ciphertext, true,
        new CryptoPP::AuthenticatedDecryptionFilter(d, new CryptoPP::StringSink(recovered)));
    std::cout << "recovered text: " << recovered << std::endl;
  }
  catch(const CryptoPP::Exception& e)
  {
    std::cerr << e.what() << std::endl;
    exit(1);
  }

  return recovered;
}


// derives PBKDF2 hash for given message using SHA-512
CryptoPP::SecByteBlock CryptoUtilities::GetPBKDF2(const std::string &message)
{

  CryptoPP::SecByteBlock salt = CryptoUtilities::GetPseudoRNG(16);
  std::string saltstring = CryptoUtilities::SecByteBlockToString(salt);
  std::cout << "Salt: " << saltstring << std::endl;

  // iterations to perform HMAC
  unsigned int iterations = 100000;

  // time in seconds to perform derivation
  double timeinSec = 1;

  // byte buffer to receive the derived password
  CryptoPP::SecByteBlock derived(CryptoPP::AES::MAX_KEYLENGTH); // 32 byte size

  // declare PBKDF2-SHA512 variable
  CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA512> pbkdf2;

  // Derive key using above parameters
  pbkdf2.DeriveKey(derived, derived.size(), 0, (const byte *)message.data(), message.size(), salt, salt.size(), iterations, timeinSec);

  std::string result = CryptoUtilities::SecByteBlockToString(derived);
  std::cout << "Derived pbkdf2: " << result << std::endl;

  return(derived); // return as a secbyte buffer
}


// AES-256 pseudorandom number generator
CryptoPP::SecByteBlock CryptoUtilities::GetPseudoRNG(const size_t &saltlen)
{
  // fetches random seed from the OS
  CryptoPP::SecByteBlock seed(32); // 32 byte
  CryptoPP::OS_GenerateRandomBlock(false, seed, seed.size());

  // compute pseudorandom number
  AES_RNG prng(seed, seed.size());

  CryptoPP::SecByteBlock randomval(saltlen);
  prng.GenerateBlock(randomval, randomval.size());

  return(randomval);

}


std::string CryptoUtilities::SecByteBlockToString(CryptoPP::SecByteBlock &buffer)
{
  std::string result;
  //convert secbyteblock to std string and print key
  result.clear();
  CryptoPP::StringSource(buffer, buffer.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(result)));

  return(result);
}