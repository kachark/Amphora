

#include "amphora_interface.hpp"


AmphoraInterface::AmphoraInterface()
{
  std::cout << "Accounts loaded" << std::endl;
  amphora_backend_m.LoadAccountList();

  // std::string viewstyle = "short";
  // std::string sortchoice = "test";
  // amphora_backend_m.ViewAccountList(viewstyle, sortchoice);
}

void AmphoraInterface::MainMenu(std::string &userinput)
{

  // Add account
  if(userinput == "1") {
    AmphoraInterface::AddAccountSubmenu();
  }

  // edit existing account
  else if(userinput == "2") { // edit account
    //list the accounts in nice tabular format, and allow the user to select the one that they want to edit.
    //AmphoraInterface::EditAccount();
  }

  // delete account
  else if(userinput == "3") {
    //go into the xml file and delete the necessary index
    //AmphoraInterface::delete_account();
  }

  else if(userinput == "4") {
    AmphoraInterface::ViewAccountsSubmenu();
  }

  // Advanced optios (TBD)
  else if(userinput == "4") {
      //choose Encryption options, fingerprint scanner support, secure password generator etc.
      //AmphoraInterface::advanced_options();
  }

}

void AmphoraInterface::AddAccountSubmenu()
{

  std::string submenu;
  Account newaccount;

  // let's user initialize the new account
  amphora_backend_m.InitAccount(newaccount);

  while(1) {
    std::cout << "\nIs the information correct?\n";
    amphora_backend_m.ViewAccount(newaccount);
    std::cout << "\n(1): Save account\n(2): Edit account\n(3): Return to Main Menu without saving\n";
    getline(std::cin, submenu);

    if(submenu == "1") {
      std::cout << "Saving account..." << std::endl;
      amphora_backend_m.SaveAccountList(newaccount);
      break;
    }

    // edit new account before saving
    else if(submenu == "2") {
      std::cout << "\n****** Editing account..." << std::endl;
      amphora_backend_m.EditAccount(newaccount);
    }

    //return to mainmenu without creating/saving new account
    else if(submenu == "3") {
      std::cout << "\nAccount not saved.\n";
      std::cout << "\nReturning to Main Menu...\n";
      break;
    }
  }

}

void AmphoraInterface::EditAccountSubmenu()
{
  // stuff
  // dialogue asking which account out of the list to edit
}

void AmphoraInterface::DeleteAccountSubmenu()
{
  // stuff
}

void AmphoraInterface::ViewAccountsSubmenu()
{
  std::string viewstyle = "long";
  std::string sortchoice = "test";
  amphora_backend_m.ViewAccountList(viewstyle, sortchoice);
}

void AmphoraInterface::OptionsSubmenu()
{
  // stuff
}

