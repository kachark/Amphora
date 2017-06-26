

#include "crypto_util.hpp"
#include "AES_RNG.h"
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/aes.h>
#include <cryptopp/gcm.h>
#include <cryptopp/modes.h>
// #include <cryptopp/drgb.h>
#include <iostream>


// encrypts account information using AES in GCM mode
std::string CryptoUtilities::Encrypt(std::string customkey)
{

  CryptoPP::AutoSeededRandomPool prng;
  CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
  prng.GenerateBlock(key, key.size());
  CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
  prng.GenerateBlock(iv, iv.size());

  std::cout << "key length: " << CryptoPP::AES::DEFAULT_KEYLENGTH << std::endl;
  std::cout << "key length (min): " << CryptoPP::AES::MIN_KEYLENGTH << std::endl;
  std::cout << "key length (max): " << CryptoPP::AES::MAX_KEYLENGTH << std::endl;
  std::cout << "block size: " << CryptoPP::AES::BLOCKSIZE << std::endl;

  std::string plaintext = "HELLOWORLD! GCM";
  std::string ciphertext, encoded, recovered;

  //pretty print key
  encoded.clear();
  CryptoPP::StringSource(key, key.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
  std::cout << "key: " << encoded << std::endl;

  //pretty print iv
  encoded.clear();
  CryptoPP::StringSource(iv, iv.size(), true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
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
  // pretty print
  encoded.clear();
  CryptoPP::StringSource(ciphertext, true,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
  std::cout << "cipher text: " << encoded << std::endl;

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

  return "";

}


std::string CryptoUtilities::Decrypt(std::string ciphertext)
{
  std::string decryptedtext;
  // key and IV setup
  byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
  memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
  memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

  //dump cipher text
  std::cout << "Cipher Text (" << ciphertext.size() << " bytes)" << std::endl;
  for( int i=0; i<ciphertext.size(); i++) {
    std::cout << "0x" << std::hex << (0xFF & static_cast<byte>(ciphertext[i])) << " ";
  }
  std::cout << std::endl << std::endl;

  //decrypt
  CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
  CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

  CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
  stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size());
  stfDecryptor.MessageEnd();

  //dump decrypted text
  std::cout << "Decrypted Text: " << std::endl;
  std::cout << decryptedtext;
  std::cout << std::endl << std::endl;

  return 0;
}


// derives PBKDF2 hash for given message using SHA-512
std::string CryptoUtilities::GetPBKDF2(const std::string &message)
{
  //safely convert std::string inputs to unsigned char (byte) ensuring no buffer overflow
  size_t messagelength = message.length();

  // memory allocation of messagelength+1 chars
  // char* password = new char[messagelength+1];
  if (messagelength > 255) {
    std::cout << "Buffer overflow" << std::endl;
    return("");
  }
  char password[messagelength + 1];
  std::strcpy(password, message.c_str());

  std::string sal = CryptoUtilities::GetSalt(16);
  char salt[sal.length() + 1];
  std::strcpy(salt, sal.c_str());
  size_t slen = strlen((const char*)salt);

  // iterations to perform HMAC
  unsigned int iterations = 20000;

  // time in seconds to perform derivation
  double timeinSec = 1;

  // byte buffer to receive the derived password
  unsigned char derived[20];
  size_t derivedlen = sizeof(derived);

  // declare PBKDF2-SHA512 variable
  CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA512> pbkdf2;

  // Derive key using above parameters
  // pbkdf2.DeriveKey(derived, sizeof(derived), 0, password, plen, salt, slen, iterations, timeinSec);
  pbkdf2.DeriveKey(derived, derivedlen, 0, (unsigned char*)password, messagelength, (unsigned char*)salt, slen, iterations);

  // encode result into hex and release as a string
  std::string result;
  CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(result));

  // places encoded result in 'derived'
  encoder.Put(derived, derivedlen);
  encoder.MessageEnd();
  std::cout << "derived in pbkdf2: " << derived << std::endl;

  return(result);
}


// AES_RNG salt
// uses AES-256
std::string CryptoUtilities::GetSalt(const size_t &saltlen)
{
  // fetches random seed from the OS
  CryptoPP::SecByteBlock seed(32);
  CryptoPP::OS_GenerateRandomBlock(false, seed, seed.size());

  // compute salt
  AES_RNG prng(seed, seed.size());

  CryptoPP::SecByteBlock t(saltlen);
  prng.GenerateBlock(t, t.size());

  std::string result;
  CryptoPP::HexEncoder hex(new CryptoPP::StringSink(result));

  hex.Put(t, t.size());
  hex.MessageEnd();

  return(result);

}


