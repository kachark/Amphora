
#ifndef AMPHORA_INTERFACE_HPP
#define AMPHORA_INTERFACE_HPP

#include "amphora_backend.hpp"

class AmphoraInterface {

public:
  AmphoraInterface();
  void MainMenu(std::string &userinput);

private:
  AmphoraBackend amphora_backend_m;
  void AddAccountSubmenu();
  void EditAccountSubmenu();
  void DeleteAccountSubmenu();
  void ViewAccountsSubmenu();
  void OptionsSubmenu();

};


#endif // AMPHORA_INTERFACE_HPP
