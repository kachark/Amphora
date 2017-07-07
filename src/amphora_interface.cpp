

#include "amphora_interface.hpp"
#include <iostream>


AmphoraInterface::AmphoraInterface()
{
  exit_flag = false;
  // log in screen test
  std::cout << "Welcome to AMPHORA" << std::endl;

  // TODO
  // load users -> log in -> load accounts only if successful
  bool loadaccounts = account_manager_m.LoadAccountList();
  if(loadaccounts) {
    std::cout << "Accounts loaded" << std::endl;
  } else if (!loadaccounts) {
    std::cout << "LOAD FAILED" << std::endl;
    // AmphoraInterface::AddAccountSubmenu();
  }
  std::cout << "Press '~' at any time to return to the main menu" << std::endl;
}

void AmphoraInterface::Start()
{
  AmphoraInterface::LoadUserFile();
  //AmphoraInterface::LogIn();
  AmphoraInterface::MainMenu();
  // if (exit_flag == true) {
  //   return;
  // }
}

void AmphoraInterface::LogIn()
{
  std::string username, password, input;
  while(1) {
    std::cout << "LOG IN" << std::endl;
    std::cout << "\n(1): Log In\n(2): Register new user\n(~): Quit" << std::endl;
    getline(std::cin, input);
    if (input == "~") {
      // exit(0); // bad - doesn't permorm clean up
      exit_flag = true;
      return;
    } else if (input == "1") {
      std::cout << "Username: ";
      getline(std::cin, username);
      std::cout << "Password: ";
      getline(std::cin, password);
      bool check = user_manager_m.CheckUser(username, password);

      if (check == false) {
        std::cout << "Your username or password are not recognized! Please reenter or register. " << std::endl;
      } else {
        AmphoraInterface::MainMenu();
      }

    } else if (input == "2") {
      AmphoraInterface::RegisterUser();
    }


    //TODO implement
    // call on backend to check if username/pw is stored and matches!!
    // if (username != dbusername || password != dbpassword) {
    //   std::cout << "Username or Password not recognized!" << std::endl;
    //   AmphoraInterface::RegisterUser();
    // } else {
    //   break;
    // }
  }
}

void AmphoraInterface::RegisterUser()
{
  std::string username, password, confirmedpw;
  while (1) {
    std::cout << "USER REGISTRATION" << std::endl;
    std::cout << "\nPlease enter a new username and password" << std::endl;
    std::cout << "Username: ";
    getline(std::cin, username);
    std::cout << "Password: ";
    getline(std::cin, password);
    std::cout << "Confirm password: ";
    getline(std::cin, confirmedpw);

    if (password != confirmedpw) {
      std::cout << "Please ensure your password is correctly entered" << std::endl;
    } else {
      break;
    }

    // TODO
    // need to store key, hmac iterations, key length (bytes), salt
    // need to have vectors of salts, key lengths, iterations, keys and serialize them
    // may need to create a class for hash and encryption settings - they should be stored independent of the Users/Accounts
    // inside crypto_util:
      // need a method to convert string to secbyteblock
      // getpbkdf2 needs to be able to take in: salt, yourmsg, iterations, key length, # bytes
      // encrypt needs: plaintext, key (encryption settings already accounted for when key and iv made ie. key.size())
      // decrypt needs: ciphertext pw/account info, # bytes, key

    // // TEST OF ENCRYPTION ON HASHING
    // CryptoPP::SecByteBlock somekey = crypto_util_m.GetPBKDF2(password);
    // // need to convert key to string to save

    // CryptoPP::SecByteBlock iv = crypto_util_m.GetPseudoRNG(16);
    // // need to convert iv to string to save

    // std::string ciphertext;
    // ciphertext = crypto_util_m.Encrypt(somekey, iv);

    // std::string decrypted;
    // decrypted = crypto_util_m.Decrypt(ciphertext, somekey, iv);

    // CryptoPP::SecByteBlock salttest = crypto_util_m.GetPseudoRNG(32);
    // std::string salt = crypto_util_m.SecByteBlockToString(salttest);
    // std::cout << "Salt: " << salt << std::endl;

    // TODO
    // needs an exit point (or does it?)
    // hash username, password with pbkdf2, store salt
    // serialize username, password, and salts
  }
}

void AmphoraInterface::MainMenu()
{
  std::string userinput;
  while(1) {
    std::cout << "\n\n****** MAIN MENU ******\n";

    // User actions
    std::cout << "\n(1): Add account\n(2): Edit account\n(3): Delete account\n(4): View Accounts\n(5): Options\n(6): Quit\n\n";

    getline(std::cin, userinput);

    if(userinput == "6") {
      // stuff have to change this actually make it exit
      std::cout << "Exiting App..." << std::endl;
      break;
    }


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
}

void AmphoraInterface::LoadUserFile()
{
  std::string input;
  bool loadusers = user_manager_m.LoadUserList();
  if(loadusers) {
    std::cout << "Users loaded" << std::endl;
  } else if (!loadusers) {
    std::cout << "vault2.xml LOAD FAILED" << std::endl;
    std::cout << "Would you like to register a new user?" << std::endl;

    while (1) {
      std::cout << "(1): yes\n" << "(2): no" << std::endl;
      getline(std::cin, input);
      if (input == "1") {
        AmphoraInterface::RegisterUser();
        break;
      } else if (input == "2") {
        exit_flag = true;
        break;
      } else {
        std::cout << "Command not recognized" << std::endl;
      }
    }
  }
}


void AmphoraInterface::AddAccountSubmenu()
{
  std::string submenu;
  std::string name, purpose, username, password;

  std::cout << "first time creating account" << std::endl;

  while(1) {
    std::cout << "Please enter the name of the account\n";
    getline(std::cin, name);

    if (name == "~") {
      return;
    } else if (account_manager_m.FindAccount(name)) {
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

  account_manager_m.AddAccount(name, purpose, username, password);
  // this needs to change
  AmphoraInterface::VerifyAddAccountPopup(name);

}


void AmphoraInterface::EditAccountSubmenu()
{
  std::string userinput;
  std::string f = "long";
  std::string s = "test";
  account_manager_m.ViewAccountList(f,s);

  while(1) {
    std::cout << "\nPlease type in the name of the account you would like to edit" << std::endl;
    getline(std::cin, userinput);

    if (userinput == "~") {
      return;
    } else if (account_manager_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      account_manager_m.EditAccount(userinput);
      account_manager_m.SaveAccountList();
      std::cout << std::endl;
      break;
    } else {
      std::cout << "\nPlease re-enter the name of the account you would like to edit" << std::endl;
    }
  }
}


void AmphoraInterface::DeleteAccountSubmenu()
{
  std::string userinput;
  std::string f = "long";
  std::string s = "test";
  account_manager_m.ViewAccountList(f, s);

  while(1) {
    std::cout << "\nPlease type in the name of the account you would like to delete" << std::endl;
    getline(std::cin, userinput);

    if (userinput == "~") {
      return;
    } else if (account_manager_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      AmphoraInterface::VerifyDeleteAccountPopup(userinput);
      break;
    } else {
      std::cout << "\nPlease re-enter the name of the account you would like to delete" << std::endl;
    }
  }
}


// user should be able select the account they want to view.
void AmphoraInterface::ViewAccountsSubmenu()
{
  std::string viewstyle = "long";
  std::string sortchoice = "test";
  account_manager_m.ViewAccountList(viewstyle, sortchoice);
}


void AmphoraInterface::OptionsSubmenu()
{
  // stuff
}


// Asks user to verify their entry
void AmphoraInterface::VerifyAddAccountPopup(const std::string &accountname)
{
  std::string submenu;
  while(1) {
    std::cout << "\nIs the information correct?\n";
    account_manager_m.ViewAccount(accountname);
    std::cout << "\n(1): Save account\n(2): Edit account\n(3): Return to Main Menu without saving\n";
    getline(std::cin, submenu);

    if(submenu == "1") {
      std::cout << "Saving account..." << std::endl;
      account_manager_m.SaveAccountList();
      break;
    }

    // edit new account before saving
    else if(submenu == "2") {
      std::cout << "\n****** Editing account..." << std::endl;
      account_manager_m.EditAccount(accountname);
    }

    //return to mainmenu without creating/saving new account
    else if(submenu == "3") {
      std::cout << "\nAccount not saved.\n";
      std::cout << "\nReturning to Main Menu...\n";
      account_manager_m.DeleteAccount(accountname);
      break;
    }
  }
}


// Asks user to verify their entry
void AmphoraInterface::VerifyDeleteAccountPopup(const std::string &accountname)
{
  std::string userinput;
  std::cout << "\nAre you sure you want to delete this account (y/n)?" << std::endl;
  std::cout << "*** " << accountname << " ***" << std::endl;
  getline(std::cin, userinput);
  if(userinput == "y" || userinput == "Y") {
    account_manager_m.DeleteAccount(accountname);
    account_manager_m.SaveAccountList();
    std::cout << "Account deleted!" << std::endl;
  } else if(userinput == "n" || userinput == "N") {
    return;
  }
}

