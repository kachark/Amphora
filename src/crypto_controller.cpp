

#include "crypto_controller.hpp"

namespace amphora {
namespace core {

CryptoController::CryptoController() {}

internal::Crypto &CryptoController::get_crypto(const std::string &fileid) {
  return crypto_m;
}

void CryptoController::AddCrypto(const std::string &fileid,
                                 std::size_t saltsize, std::size_t ivsize,
                                 std::size_t keysize, unsigned int iterations) {
  internal::Crypto crypto;
  crypto.set_saltsize(saltsize);
  crypto.set_ivsize(ivsize);
  crypto.set_keysize(keysize);
  crypto.set_hmac_iterations(iterations);
  crypto_m = crypto;
}

// load crypto config file json
bool CryptoController::LoadCrypto() {
  // bool loadstatus;
  // std::string filename = "../data/user/" + fileid + ".xml";
  // std::cout << filename << std::endl;
  // std::vector<Account> accountvector;
  // if (amphora_util_m.FindFile(filename)) {  // check if file exists in
  // directory
  //   std::cout << "File found" << std::endl; // debug
  //   loadstatus = amphora_util_m.LoadFromFile<Account>(filename,
  //   accountvector); if (loadstatus) { // if load success + check file ->
  //   return true
  //     // populate memory
  //     for (auto account : accountvector) {
  //       accountlist_m.insert(std::make_pair(account.get_name(), account));
  //     }
  //     return true;
  //   }
  // }
  // return false;
  return false;
}
bool CryptoController::SaveCrypto() { return true; }
void CryptoController::ViewConfig() {}

} // namespace core
} // namespace amphora
