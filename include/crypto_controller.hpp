
#ifndef CRYPTO_CONTROLLER_HPP
#define CRYPTO_CONTROLLER_HPP

#include "crypto.hpp"
#include <string>

namespace amphora {
namespace core {

class CryptoController {

public:
  CryptoController();

  internal::Crypto &get_crypto(const std::string &fileid);

  void AddCrypto(const std::string &fileid, std::size_t saltsize,
                 std::size_t ivsize, std::size_t keysize,
                 unsigned int iterations);

  // TODO
  // return error type: 0 = fail, 1 = pass
  bool LoadCrypto();
  bool SaveCrypto();

  void ViewConfig();

private:
  internal::Crypto crypto_m;
};

} // namespace core
} // namespace amphora

#endif // CRYPTO_CONTROLLER_HPP
