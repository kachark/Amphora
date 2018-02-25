
#ifndef CRYPTO_CONTROLLER_HPP
#define CRYPTO_CONTROLLER_HPP

#include "amphora_util.hpp"
#include "crypto.hpp"
#include <string>
#include <memory>

class CryptoController {

 public:
//  CryptoController() = default;
//
//  CryptoController(const CryptoController &c);
//
//  ~CryptoController() = default;

  Crypto &get_crypto(const std::string &fileid);

  void AddCrypto(const std::string &fileid, std::size_t saltsize,
                 std::size_t ivsize, std::size_t keysize,
                 unsigned int iterations);

  // TODO
  // return error type: 0 = fail, 1 = pass
  bool LoadCrypto(std::weak_ptr<AmphoraUtilities> wP_util, const std::string &filename);

  bool SaveCrypto(std::weak_ptr<AmphoraUtilities> wP_util, const std::string &filename);

  void ViewConfig();

 private:

  Crypto crypto_m;
};

#endif // CRYPTO_CONTROLLER_HPP
