
#ifndef CRYPTO_CONTROLLER_HPP
#define CRYPTO_CONTROLLER_HPP

#include "amphora_mediator.hpp"
#include "crypto.hpp"
#include <string>

class AmphoraMediator;

class CryptoController {

public:
  // TODO p1-1 copy constructor and destructor
  CryptoController(const AmphoraMediator &m);
  CryptoController(const CryptoController &c);
  ~CryptoController();

  Crypto &get_crypto(const std::string &fileid);

  void AddCrypto(const std::string &fileid, std::size_t saltsize,
                 std::size_t ivsize, std::size_t keysize,
                 unsigned int iterations);

  // TODO
  // return error type: 0 = fail, 1 = pass
  bool LoadCrypto();
  bool SaveCrypto();

  void ViewConfig();

private:
  AmphoraMediator mediator_m;

  Crypto crypto_m;
};

#endif // CRYPTO_CONTROLLER_HPP
