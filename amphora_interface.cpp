

#include "amphora_interface.hpp"


AmphoraInterface::AmphoraInterface()
{
  amphora_backend_m.LoadAccountList();
  std::cout << "Accounts loaded" << std::endl;
}

void AmphoraInterface::MainMenu(const std::string &userinput)
{

  // Add account
  if(userinput == "1") {
    AmphoraInterface::AddAccountSubmenu();
  }

  // edit existing account
  else if(userinput == "2") { // edit account
    AmphoraInterface::EditAccountSubmenu();
  }

  // delete account
  else if(userinput == "3") {
    //go into the xml file and delete the necessary index
    AmphoraInterface::DeleteAccountSubmenu();
  }

  else if(userinput == "4") {
    AmphoraInterface::ViewAccountsSubmenu();
  }

  // Advanced optios (TBD)
  else if(userinput == "5") {
      //choose Encryption options, fingerprint scanner support, secure password generator etc.
      //AmphoraInterface::advanced_options();
  }
}


void AmphoraInterface::AddAccountSubmenu()
{
  std::string submenu;
  std::string name, purpose, username, password;


  // check if account is presently stored
  // if yes: query user to change the name of the account
  // if no: add the new account

  // always give the user a way to return to the Main Menu

  // populate account object members for the first time
  std::cout << "first time creating account" << std::endl;

  while(1) {
    std::cout << "Please enter the name of the account\n";
    getline(std::cin, name);

    if (amphora_backend_m.FindAccount(name)) {
      std::cout << "The account name you entered is already in use. Please enter a new name for the account." << std::endl;
    } else {
    std::cout << "Please enter the purpose of the account\n";
    getline(std::cin, purpose);

    std::cout << "Please enter the username for this account\n";
    getline(std::cin, username);

    std::cout << "Please enter the password for this account\n";
    getline(std::cin, password);
    break;
    }
  }

  amphora_backend_m.AddAccount(name, purpose, username, password);

  while(1) {
    std::cout << "\nIs the information correct?\n";
    amphora_backend_m.ViewAccount(name);
    std::cout << "\n(1): Save account\n(2): Edit account\n(3): Return to Main Menu without saving\n";
    getline(std::cin, submenu);

    if(submenu == "1") {
      std::cout << "Saving account..." << std::endl;
      amphora_backend_m.SaveAccountList();
      break;
    }

    // edit new account before saving
    else if(submenu == "2") {
      std::cout << "\n****** Editing account..." << std::endl;
      amphora_backend_m.EditAccount(name);
    }

    //return to mainmenu without creating/saving new account
    else if(submenu == "3") {
      std::cout << "\nAccount not saved.\n";
      std::cout << "\nReturning to Main Menu...\n";
      amphora_backend_m.DeleteAccount(name);
      break;
    }
  }
}


void AmphoraInterface::EditAccountSubmenu()
{
  std::string userinput;
  std::string f = "long";
  std::string s = "test";
  amphora_backend_m.ViewAccountList(f,s);

  while(1) {
    std::cout << "\nPlease type in the name of the account you would like to edit" << std::endl;
    getline(std::cin, userinput);
    if (amphora_backend_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      amphora_backend_m.EditAccount(userinput);
      amphora_backend_m.SaveAccountList();
      std::cout << std::endl;
      break;
    } else if (amphora_backend_m.FindAccount(userinput) == false) {
      std::cout << "\nPlease re-enter the name of the account you would like to edit" << std::endl;
    }
  }
}


void AmphoraInterface::DeleteAccountSubmenu()
{
  std::string userinput;

  while(1) {
    std::cout << "\nPlease type in the name of the account you would like to delete" << std::endl;
    getline(std::cin, userinput);
    if (amphora_backend_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      amphora_backend_m.DeleteAccount(userinput);
      amphora_backend_m.SaveAccountList();
      std::cout << std::endl;
      break;
    } else {
      std::cout << "\nPlease re-enter the name of the account you would like to delete" << std::endl;
    }
  }
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

