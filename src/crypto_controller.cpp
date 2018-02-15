

#include "crypto_controller.hpp"

CryptoController::CryptoController(const AmphoraMediator &mediator)
        : mediator_m(mediator) {}

Crypto &CryptoController::get_crypto(const std::string &fileid) {
    return crypto_m;
}

/* Updates current Crypto configuration */
void CryptoController::AddCrypto(const std::string &fileid,
                                 std::size_t saltsize, std::size_t ivsize,
                                 std::size_t keysize, unsigned int iterations) {
    Crypto crypto;
    crypto.set_saltsize(saltsize);
    crypto.set_ivsize(ivsize);
    crypto.set_keysize(keysize);
    crypto.set_hmac_iterations(iterations);
    crypto_m = crypto;
}

// TODO p1-6
/* Load crypto configuration */
bool CryptoController::LoadCrypto() {
    // bool loadstatus;
    // std::string filename = "../data/user/" + fileid + ".xml";
    // std::cout << filename << std::endl;
    // std::vector<Account> accountvector;
    // if (amphora_util_m.FindFile(filename)) {  // check if file exists in
    // directory
    //   std::cout << "File found" << std::endl; // debug
    //   loadstatus = amphora_util_m.Load<Account>(filename,
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
