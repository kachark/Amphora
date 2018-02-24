
#ifndef AMPHORA_MEDIATOR_HPP
#define AMPHORA_MEDIATOR_HPP

#include "account.hpp"
#include "crypto.hpp"
#include "user.hpp"
#include "amphora_types.hpp"
#include "amphora_types.hpp"
#include "amphora_util.hpp"
#include "amphora_config.hpp"
#include "account_controller.hpp"
#include "user_controller.hpp"
#include "crypto_controller.hpp"
#include "crypto_util.hpp"
#include <memory>
#include <string>

class AmphoraMediator {

 public:
  AmphoraMediator() = default;

  ~AmphoraMediator() = default;

  AmphoraMediator(const AmphoraMediator &m);

  AmphoraMediator &operator=(const AmphoraMediator &m);

  void Setup();

  /* Users */
  void NewUser(const std::string &username, const std::string &password); // ?

  void DeleteUser(const std::string &username, const std::string &password);

  bool VerifyUser(const std::string &username, const std::string &password);

  bool CheckUser(const std::string &username);

  void UpdateCurrentUser(const std::string &username);

  void NewAccount(const std::string &name, const std::string &purpose,
                  const std::string &username, const std::string &password);

  Account GetAccount(const std::string &accountname);

  void ShowSession();

  void ShowAccount();

  /* Utils */
  std::string get_date();

  bool Load(AmphoraType id);

  bool Save(AmphoraType id);

 private:

//  class AmphoraUtilities;
//  class AmphoraConfig;
//  class AccountController;
//  class CryptoController;
//  class UserController;
//  class CryptoUtilities;

    // TODO p1-4
  template<typename T>
  void Encrypt(T, AmphoraType id);

  template<typename T>
  void Decrypt(T, AmphoraType id);

  bool VerifyCrypto(const User &user, const std::string &password);

  AccountController account_controller_m;
  CryptoController crypto_controller_m;
  UserController user_controller_m;
  CryptoUtilities crypto_util_m;
//    Logger logger_m;
//    AmphoraUtilities amphora_util_m;
  AmphoraConfig amphora_config_m;

//    std::unique_ptr<AccountController> account_controller_m;
//    std::unique_ptr<CryptoController> crypto_controller_m;
//    std::unique_ptr<UserController> user_controller_m;
//    std::unique_ptr<CryptoUtilities> crypto_util_m;
//    std::unique_ptr<AmphoraConfig> amphora_config_m;
//    // std::unique_ptr<Logger> logger_m;
  std::shared_ptr<AmphoraUtilities> amphora_util_m;

  // TODO
  /* Status flags */
  bool users_loaded_m;
  bool crypto_loaded_m;
  bool accounts_loaded_m;
  bool config_loaded_m;

  User current_user_m;
  Crypto current_crypto_m;
  // Error error_m;

};

#endif // AMPHORA_MEDIATOR_HPP
