
#ifndef AMPHORA_INTERFACE_HPP
#define AMPHORA_INTERFACE_HPP

#include "account_manager.hpp"
#include "amphora_util.hpp"
#include "crypto_db.hpp"
#include "crypto_manager.hpp"
#include "crypto_util.hpp"
#include "user_manager.hpp"
#include <string>

class AmphoraInterface {

public:
  AmphoraInterface();
  void Start();
  void LogIn();
  void MainMenu();
  void RegisterUser();
  // void MainMenu(const std::string &userinput);

protected:
  std::string currentfileid_m;

private:
  AmphoraBackend::AccountManager account_manager_m;
  AmphoraBackend::UserManager user_manager_m;
  AmphoraBackend::CryptoManager crypto_manager_m;
  CryptoUtilities crypto_util_m;
  // CryptoDB cryptodb_m;
  // AmphoraUtilities amphora_util_m;
  bool exit_flag_m;
  static const unsigned int maxlogins_m = 3;

  void Exit();
  void test();
  void LoadUserFile();
  void LoadAccountFile(const std::string &fileid);
  void AddAccountSubmenu();
  void EditAccountSubmenu();
  void DeleteAccountSubmenu();
  void ViewAccountsSubmenu();
  void OptionsSubmenu();
  void VerifyAddAccountPopup(const std::string &accountname);
  void VerifyDeleteAccountPopup(const std::string &accountname);
};

#endif // AMPHORA_INTERFACE_HPP
