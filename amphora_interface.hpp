
#ifndef AMPHORA_INTERFACE_HPP
#define AMPHORA_INTERFACE_HPP

#include "amphora_backend.hpp"

class AmphoraInterface {

public:
  AmphoraInterface();
  void MainMenu(const std::string &userinput);

private:
  AmphoraBackend amphora_backend_m;
  void AddAccountSubmenu();
  void EditAccountSubmenu();
  void DeleteAccountSubmenu();
  void ViewAccountsSubmenu();
  void OptionsSubmenu();
  void VerifyAddAccountPopup(const std::string &accountname);
  void VerifyDeleteAccountPopup(const std::string &accountname);
};


#endif // AMPHORA_INTERFACE_HPP
