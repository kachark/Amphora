
#ifndef AMPHORA_INTERFACE_HPP
#define AMPHORA_INTERFACE_HPP

#include "account_manager.hpp"
#include "user_manager.hpp"
#include "amphora_util.hpp"
#include <string>

class AmphoraInterface {

public:
  AmphoraInterface();
  void Start();
  void LogIn();
  void MainMenu();
  void RegisterUser();
  // void MainMenu(const std::string &userinput);

private:
  AmphoraBackend::AccountManager account_manager_m;
  AmphoraBackend::UserManager user_manager_m;
  //AmphoraUtilities amphora_util_m;
  bool exit_flag;

  void Exit();
  void LoadUserFile();
  void AddAccountSubmenu();
  void EditAccountSubmenu();
  void DeleteAccountSubmenu();
  void ViewAccountsSubmenu();
  void OptionsSubmenu();
  void VerifyAddAccountPopup(const std::string &accountname);
  void VerifyDeleteAccountPopup(const std::string &accountname);
};


#endif // AMPHORA_INTERFACE_HPP
