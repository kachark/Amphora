
#include "amphora_mediator.hpp"
#include "account_controller.hpp"
#include "amphora_util.hpp"
#include "crypto_controller.hpp"
#include "crypto_util.hpp"
#include "user_controller.hpp"
#include <cryptopp/secblock.h>

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

  current_crypto_m = crypto_controller_m->get_crypto("default");

  // LoadUsers();
  // LoadCrypto();
  // LoadAccountList();
}

/* Returns current date as string */
std::string AmphoraMediator::get_date() {
  return amphora_util_m->CurrentDate();
}

void AmphoraMediator::UpdateCurrentUser(const std::string &username) {
  current_user_m = user_controller_m->get_user(username);
  current_crypto_m =
      crypto_controller_m->get_crypto(current_user_m.get_crypto_id());
}

/* Add new User */
void AmphoraMediator::NewUser(const std::string &username,
                              const std::string &password) {

  User tempuser;
  std::string date = get_date();
  unsigned int iterations = current_crypto_m.get_hmac_iterations();
  CryptoPP::SecByteBlock accountfileid = crypto_util_m->AES_PRNG(3);
  CryptoPP::SecByteBlock salt =
      crypto_util_m->AES_PRNG(current_crypto_m.get_saltsize());
  std::size_t keysize = current_crypto_m.get_keysize();
  CryptoPP::SecByteBlock hashedpassword =
      crypto_util_m->PBKDF2(iterations, salt, keysize, password);

  tempuser.set_username(username);
  tempuser.set_password(crypto_util_m->SecByteBlockToString(hashedpassword));
  tempuser.set_datecreated(date);
  tempuser.set_datemodified(date);
  tempuser.set_account_file(crypto_util_m->SecByteBlockToString(accountfileid));
  tempuser.set_crypto_id("default");
  tempuser.set_salt(crypto_util_m->SecByteBlockToString(salt));
  user_controller_m->AddUser(tempuser);
  user_controller_m->SaveUserList();

  tempuser.clear();
}

// TODO p1-6 secure container
bool AmphoraMediator::VerifyUser(const std::string &username,
                                 const std::string &password) {
  // TODO p1-4 error type
  bool userfound = CheckUser(username);
  if (!userfound) {
    // TODO p1-1
    return 0; // User not found in database
    // move this line to cli.cpp
    // std::cout << "User not found in userdata" << std::endl;
  } else { // username in database, now verify the password
    // compare this user's pw/key with what was passed into this function
    // User loggedin = userlist_m[username];
    User tmp_user = user_controller_m->get_user(username);
    bool crypto_verified = VerifyCrypto(tmp_user, password);
    if (crypto_verified) {
      return 1;
    }
  }
  return 0; // default return, user not found or bad password
}

/* Verifies a Users cryptographic credentials */
// TODO p1-1 functinality doesn't make sense
bool AmphoraMediator::VerifyCrypto(const User &user,
                                   const std::string &password) {
  // TODO p1-3 Move to it's own function, return bool
  Crypto tmp_crypto = crypto_controller_m->get_crypto(user.get_crypto_id());
  // TODO p1-6 don't st ore secure data in std::strings
  // access this user's crypto settings
  CryptoPP::SecByteBlock salt = tmp_crypto.get_salt();
  std::size_t keysize = tmp_crypto.get_keysize();
  unsigned int iterations = tmp_crypto.get_hmac_iterations();
  CryptoPP::SecByteBlock masterkey =
      crypto_util_m->PBKDF2(iterations, salt, keysize, password);

  // TODO p1-6 use cryptopp VerifyBufsEqual or similar
  // if (masterkey == loggedin.get_password()) {
  // if (masterkey.compare(loggedin.get_password())) {
  if (std::lexicographical_compare(masterkey.begin(), masterkey.end(),
                                   user.get_password().begin(),
                                   user.get_password().end())) {
    return 1;
  }
  return 0;
}

/* Checks if User exists
0: Does not exist
1: Exists */
bool AmphoraMediator::CheckUser(const std::string &username) {
  if (user_controller_m->CheckUserList(username)) {
    return true; // found
  } else {       // account key not found
    return false;
  }
}

bool AmphoraMediator::LoadUsers() { return user_controller_m->LoadUserList(); }

bool AmphoraMediator::LoadAccountList() {
  return account_controller_m->LoadAccountList(
      current_user_m.get_account_file());
}

bool AmphoraMediator::LoadCrypto() { return crypto_controller_m->LoadCrypto(); }
