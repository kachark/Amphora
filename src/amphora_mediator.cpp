
#include "amphora_mediator.hpp"
#include "account_controller.hpp"
#include "amphora_util.hpp"
#include "crypto_controller.hpp"
#include "crypto_util.hpp"
#include "user_controller.hpp"

// AmphoraMediator::AmphoraMediator(const AmphoraMediator &m) {
//   account_controller_m = m.account_controller_m;
//   crypto_controller_m = m.crypto_controller_m;
//   user_controller_m = m.user_controller_m;
//   crypto_util_m = m.crypto_util_m;
//   amphora_util_m = m.amphora_util_m;
// }

AmphoraMediator::~AmphoraMediator() {
  // delete[] account_controller_m;
  // delete[] crypto_controller_m;
  // delete[] user_controller_m;
}

AmphoraMediator &AmphoraMediator::operator=(const AmphoraMediator &rhs) {
  if (this != &rhs) {
    // delete old
    // delete[] account_controller_m;
    // delete[] crypto_controller_m;
    // delete[] user_controller_m;
    // copy from rhs
    // account_controller_m = rhs.account_controller_m;
    // crypto_controller_m = rhs.crypto_controller_m;
    // user_controller_m = rhs.crypto_controller_m;
  }
  return *this; // return reference to left-hand side
}

/* Add controllers, loggers, etc. */
void AmphoraMediator::Setup() {
  account_controller_m =
      std::unique_ptr<AccountController>(new AccountController(*this));
  crypto_controller_m =
      std::unique_ptr<CryptoController>(new CryptoController(*this));
  user_controller_m =
      std::unique_ptr<UserController>(new UserController(*this));
  crypto_util_m = std::unique_ptr<CryptoUtilities>(new CryptoUtilities(*this));
  amphora_util_m =
      std::unique_ptr<AmphoraUtilities>(new AmphoraUtilities(*this));
}
