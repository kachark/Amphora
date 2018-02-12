
#ifndef CLI_HPP
#define CLI_HPP

#include "amphora_mediator.hpp"
#include <string>

class AmphoraInterface {

public:
  AmphoraInterface();
  void Start();
  void LogIn();
  void MainMenu();
  void RegisterUser();

protected:
  void NewMediator();

private:
  // singleton mediator instance
  std::unique_ptr<AmphoraMediator> mediator_m;

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

#endif // CLI_HPP
