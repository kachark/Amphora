
#ifndef CLI_HPP
#define CLI_HPP

#include "account_controller.hpp"
#include "amphora_util.hpp"
#include "crypto.hpp"
#include "crypto_controller.hpp"
#include "crypto_util.hpp"
#include "user_controller.hpp"
#include <string>

namespace amphora {
namespace cli {

class AmphoraInterface {

public:
  AmphoraInterface();
  void Start();
  void LogIn();
  void MainMenu();
  void RegisterUser();

private:
  core::AccountController account_controller_m;
  core::UserController user_controller_m;
  core::CryptoController crypto_controller_m;
  internal::CryptoUtilities crypto_util_m;
  internal::Crypto
      crypto_m; // currently saved cryptographic settings - sizes, iterations
  internal::User
      currentuser_m; // has all the required fields for the logged in user
  std::string currentacctid_m;
  // AmphoraUtilities core_m;
  bool exit_flag_m;
  static const unsigned int MAXLOGINS_m = 3;

  void Exit();
  void test();
  void LoadUserFile();
  void LoadCryptoConfig();
  void LoadAccountFile();
  void AddAccountSubmenu();
  void EditAccountSubmenu();
  void DeleteAccountSubmenu();
  void ViewAccountsSubmenu();
  void OptionsSubmenu();
  void VerifyAddAccountPopup(const std::string &accountname);
  void VerifyDeleteAccountPopup(const std::string &accountname);
};

} // namespace cli
} // namespace amphora

#endif // CLI_HPP
