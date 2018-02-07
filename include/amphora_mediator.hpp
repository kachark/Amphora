
#ifndef AMPHORA_MEDIATOR_HPP
#define AMPHORA_MEDIATOR_HPP

#include "account.hpp"
#include "crypto.hpp"
#include "user.hpp"
#include <memory>
#include <string>

/* Forward Declarations */
class AccountController; // forward dec needs to be in correct scope
class UserController;
class CryptoController;
class CryptoUtilities;
class AmphoraUtilities;

// typedef std::unique_ptr<AccountController> AccountControllerP;
// typedef std::unique_ptr<CryptoController> CryptoControllerP;
// typedef std::unique_ptr<AccountController> UserControllerP;
// typedef std::unique_ptr<CryptoUtilities> CryptoUtilP;
// typedef std::unique_ptr<AmphoraUtilities> AmphoraUtilP;

class AmphoraMediator {

public:
  // TODO p1-1 overload = operator, copy constructor and destructor
  AmphoraMediator() = default;
  AmphoraMediator(const AmphoraMediator &m); // copy constructor
  ~AmphoraMediator();
  AmphoraMediator &operator=(const AmphoraMediator &m);

  void Setup();

  // from UserController
  void AddUser(const std::string &username); // ?
  bool VerifyUser(const std::string &username, const std::string &password);

  void ShowSession();
  void SaveSession();
  void ShowAccount();

private:
  // TODO p1-4
  void Encrypt();
  bool VerifyCrypto(const User &user, const std::string &password);
  bool FindUser(const std::string &username);

  // each of the controllers should be able to reference the mediator to
  // access the util objects
  std::unique_ptr<AccountController> account_controller_m;
  std::unique_ptr<CryptoController> crypto_controller_m;
  std::unique_ptr<UserController> user_controller_m;
  std::unique_ptr<CryptoUtilities> crypto_util_m;
  std::unique_ptr<AmphoraUtilities> amphora_util_m;
  // std::unique_ptr<Logger> logger_m;

  User current_user_m;
  Crypto current_crypto_m;
  // Error error_m;
};

#endif // AMPHORA_MEDIATOR_HPP
