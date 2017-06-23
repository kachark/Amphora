

#include "amphora_util.hpp"
#include "AES_RNG.h"
#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/osrng.h>
#include <cryptopp/secblock.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
// #include <cryptopp/drgb.h>
// #include <boost/filesystem.hpp>

using namespace boost::posix_time;


// retrieves system date and time in nice format
std::string AmphoraUtilities::CurrentDate()
{
  time_facet *facet = new time_facet("%d-%b-%Y %H:%M:%S");
  std::cout.imbue(std::locale(std::cout.getloc(), facet));
  //  cout << second_clock::local_time() << endl;
  std::string date = to_simple_string(second_clock::local_time());
  std::cout << "INSIDE get_date() -> " << date << std::endl;
  return date;
}


// encrypts account information using AES in GCM mode
std::string AmphoraUtilities::Encrypt(std::string customkey)
{
  std::cout << "inside encrypt";
  // key and IV setup
  byte key[CryptoPP::AES::DEFAULT_KEYLENGTH], iv[CryptoPP::AES::BLOCKSIZE];
  memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
  memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );

  //string and sink setup
  std::string plaintext = "hello world!";
  std::string ciphertext;
  std::string decryptedtext;

  //dump plaintext
  std::cout << "Plain Text (" << plaintext.size() << " bytes)" << std::endl;
  std::cout << plaintext;
  std::cout << std::endl << std::endl;

  //create ciphertext
  CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
  CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv);

  CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
  stfEncryptor.Put(reinterpret_cast<const unsigned char*>(plaintext.c_str() ), plaintext.length()+1);
  stfEncryptor.MessageEnd();

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

  return("");
}

// checks if a file is in the pwd
int AmphoraUtilities::CheckFile(const std::string &filename)
{
  //see boost filesystem
  return 0;
}

// outputs vector of strings in nice format
void AmphoraUtilities::PrettyTable(const std::vector<std::string> &data)
{

  // get largest string of characters
  std::size_t largestelement = 0;
  for (auto element : data) {
    std::size_t elementsize = element.length();
    if (elementsize > largestelement) {
      largestelement = elementsize;
    }
  }

  // define table format
  int numcolumns = 4;
  std::size_t columnwidth = largestelement + 2;
  char delimiterchar = ' ';

  // format table elements
  int currentcolumn = 1;
  std::size_t delimitersize = 0;
  for (auto element : data) {
    std::string delimiter;
    std::string token = element;
    std::size_t tokenlength = element.length();
    if (tokenlength != columnwidth) {
      delimitersize = columnwidth - tokenlength;
      delimiter.assign(delimitersize, delimiterchar);
      token = token + delimiter;
    }

    if (currentcolumn != numcolumns) {
      std::cout << token;
      currentcolumn += 1;
    } else if (currentcolumn == numcolumns) {
      std::cout << token << std::endl;
      currentcolumn = 1;
    }
  }
}


// derives PBKDF2 hash for given message using SHA-512
std::string AmphoraUtilities::GetPBKDF2(const std::string &message)
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

  std::string sal = AmphoraUtilities::GetSalt(16);
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

  return(result);
}


// AES_RNG salt
std::string AmphoraUtilities::GetSalt(const size_t &saltlen)
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








