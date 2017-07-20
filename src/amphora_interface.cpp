
// TODO
// make sure account_manager, user_manager, crypto_manager each have similar
// naming styles, code layout, and general functionality
// name vs username, list vs vector vs data etc etc
// TODO
// if user changes their encryption settings, reencrypt everything

#include "../include/amphora_interface.hpp"
#include <iostream>

/* Amphora Interface Constructor */
AmphoraInterface::AmphoraInterface() {
  exit_flag_m = false;
}

/* Start Amphora Interface */
void AmphoraInterface::Start() {
  std::cout << "Welcome to AMPHORA" << std::endl;
  std::cout << "Press '~' at any time to return to the main menu" << std::endl;
  AmphoraInterface::LoadCryptoFile();
  AmphoraInterface::LoadUserFile();
  AmphoraInterface::LogIn();
  AmphoraInterface::LoadAccountFile(currentfileid_m);
  AmphoraInterface::MainMenu();
}

/* Log In Page */
/* Shows options for user log in, registration, or exiting the program.
   (1) selected, asks user for username and password to verify.
   (2) Opens the RegisterUser page.
   (~) Exits the program. */
void AmphoraInterface::LogIn() {
  if (exit_flag_m == true) {
    return;
  }

  std::string username, password, input;
  unsigned int attempts = 0;
  while (attempts < maxlogins_m) {
    std::cout << "LOG IN" << std::endl;
    std::cout << "\n(1): Log In\n(2): Register new user\n(~): Quit"
              << std::endl;
    getline(std::cin, input);

    if (input == "~") {
      exit_flag_m = true;
      return;
    } else if (input == "1") {
      attempts++;
      std::cout << "Username: ";
      getline(std::cin, username);
      std::cout << "Password: ";
      getline(std::cin, password);
      bool verified =
          user_manager_m.VerifyUser(username, password, crypto_manager_m);
      if (!verified) {
        std::cout << "Your username or password are not recognized! Please "
                     "reenter or register. "
                  << std::endl;
      } else if (verified) { // logged in!
        std::cout << "Logged In!" << std::endl;
        // TODO
        // set the cryptodb to the current user!!
        User tempuser = user_manager_m.GetUser(username);
        cryptodb_m = crypto_manager_m.GetCryptoDB(tempuser.get_cryptodbname());
        break;
      }

    } else if (input == "2") {
      AmphoraInterface::RegisterUser();
    }
  }
}

/* Registration Page */
/* Asks user to enter username and password and compares them against the
 * database. If username/password is unique, the username/password is hashed. */
void AmphoraInterface::RegisterUser() {
  if (exit_flag_m == true) {
    return;
  }

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

    // check username against database
    bool usercollision = user_manager_m.FindUser(username);
    if (usercollision) {
      std::cout << "The username you entered is taken. Please enter another name" << std::endl;
    }
    if (password != confirmedpw) {
      std::cout << "Please ensure your password is correctly entered"
                << std::endl;
    } else if ((usercollision == false) && (password == confirmedpw)) { // register user
      // TODO
      // should this be in a separate function? yes
      // generate fileid for new User to create/manage Accounts
      CryptoPP::SecByteBlock fileidbyte = crypto_util_m.Get_AES_PseudoRNG(3);
      std::string accountfileid =
          crypto_util_m.SecByteBlockToString(fileidbyte);
      std::string cryptofileid = "default";
      //TODO should the db be available from RegisterUser or after log in?
      // make crypto database available to the interface
      cryptodb_m = crypto_manager_m.GetCryptoDB(cryptofileid);
      CryptoPP::SecByteBlock salt =
          crypto_util_m.Get_AES_PseudoRNG(cryptodb_m.get_saltsize());
      std::string saltstr = crypto_util_m.SecByteBlockToString(salt);
      CryptoPP::SecByteBlock test = crypto_util_m.StringToSecByteBlock(saltstr);
      std::string testsalt = crypto_util_m.SecByteBlockToString(test);
      unsigned int iterations = cryptodb_m.get_iterations();
      std::size_t keysize = cryptodb_m.get_keysize();

      CryptoPP::SecByteBlock hashedpassword =
          crypto_util_m.GetPBKDF2(iterations, salt, keysize, password);
      std::string hashedpwstr =
          crypto_util_m.SecByteBlockToString(hashedpassword);
      user_manager_m.AddUser(username, hashedpwstr, saltstr, accountfileid,
                             cryptofileid);
      user_manager_m.SaveUserList();

      // add current user fileid to amphora interface to access their accounts
      // file
      currentfileid_m = accountfileid;
      break;
    }
  }
}

void AmphoraInterface::MainMenu() {
  if (exit_flag_m == true) {
    return;
  }

  std::string userinput;
  while (1) {
    std::cout << "\n\n****** MAIN MENU ******\n";

    // User actions
    std::cout << "\n(1): Add account\n(2): Edit account\n(3): Delete "
                 "account\n(4): View Accounts\n(5): Options\n(6): Quit\n\n";

    getline(std::cin, userinput);

    if (userinput == "6") {
      // stuff have to change this actually make it exit
      std::cout << "Exiting App..." << std::endl;
      break;
    }

    // Add account
    if (userinput == "1") {
      AmphoraInterface::AddAccountSubmenu();
    }

    // edit existing account
    else if (userinput == "2") { // edit account
      AmphoraInterface::EditAccountSubmenu();
    }

    // delete account
    else if (userinput == "3") {
      // go into the xml file and delete the necessary index
      AmphoraInterface::DeleteAccountSubmenu();
    }

    else if (userinput == "4") {
      AmphoraInterface::ViewAccountsSubmenu();
    }

    // TODO
    // config file for encryption settings
    // edit user settings - password
    // Advanced optios (TBD)
    else if (userinput == "5") {
      // choose Encryption options, fingerprint scanner support, secure
      // password
      // generator etc.
      // AmphoraInterface::advanced_options();
    }
  }
}

/* Load User File */
/* Attempts to load Users into memory from user file. If Users are unable to be
 * loaded, it will give the user the option of registering. */
void AmphoraInterface::LoadUserFile() {
  if (exit_flag_m == true) {
    return;
  }
  std::string input;
  bool loadusers = user_manager_m.LoadUserList();
  if (loadusers) {
    std::cout << "Users loaded" << std::endl;
  } else if (!loadusers) {
    std::cout << "User File LOAD FAILED" << std::endl;
    std::cout << "Would you like to register a new user?" << std::endl;

    while (1) {
      std::cout << "(1): yes\n"
                << "(2): no" << std::endl;
      getline(std::cin, input);
      if (input == "1") {
        AmphoraInterface::RegisterUser();
        break;
      } else if (input == "2") {
        exit_flag_m = true;
        break;
      } else {
        std::cout << "Command not recognized" << std::endl;
      }
    }
  }
}

/* Load Crypto Settings File */
/* Attempts to load Crypto Settings into memory from crypto file. If CryptoDB is
 * unable to be loaded, it will resort to default settings. */
void AmphoraInterface::LoadCryptoFile() {
  if (exit_flag_m == true) {
    return;
  }
  bool loaded = crypto_manager_m.LoadCryptoDB();
  if (loaded) {
    std::cout << "Crypto settings loaded" << std::endl;
  } else if (!loaded) {
    std::cout << "Crypto settings LOAD FAILED" << std::endl;
    std::cout << "Reverting to default settings!" << std::endl;
    std::cout << "Salt Size: 16 bytes\nIV Size: 16 bytes\nKey Size: 32 "
                 "bytes\nHMAC Iterations: 200,000"
              << std::endl;
    std::size_t saltsize = 16;
    std::size_t ivsize = 16;
    std::size_t keysize = 32;
    unsigned int iterations = 200000;
    crypto_manager_m.AddCryptoDB("default", saltsize, ivsize, keysize,
                                 iterations);
    crypto_manager_m.SaveCryptoDB();
  }
}

/* Load Account File */
/* Loads Account File for the currently logged in User */
void AmphoraInterface::LoadAccountFile(const std::string &fileid) {
  if (exit_flag_m == true) {
    return;
  }

  bool loadaccounts = account_manager_m.LoadAccountList(fileid);
  if (loadaccounts) {
    std::cout << "Accounts loaded" << std::endl;
  } else if (!loadaccounts) {
    std::cout << "LOAD FAILED" << std::endl;
    // AmphoraInterface::AddAccountSubmenu();
  }
}

/* Add Account */
/* Presents the user with the option of adding new Accounts that they would like
 * to save */
void AmphoraInterface::AddAccountSubmenu() {
  std::string submenu;
  std::string name, purpose, username, password;

  std::cout << "first time creating account" << std::endl;

  while (1) {
    std::cout << "Please enter the name of the account\n";
    getline(std::cin, name);

    if (name == "~") {
      return;
    } else if (account_manager_m.FindAccount(name)) {
      std::cout << "The account name you entered is already in use. Please "
                   "enter a new name for the account."
                << std::endl;
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

/* Edit Account */
/* Presents the user with the option of editing Accounts that they have saved */
void AmphoraInterface::EditAccountSubmenu() {
  std::string userinput;
  std::string f = "long";
  std::string s = "test";
  account_manager_m.ViewAccountList(f, s);

  while (1) {
    std::cout
        << "\nPlease type in the name of the account you would like to edit"
        << std::endl;
    getline(std::cin, userinput);

    if (userinput == "~") {
      return;
    } else if (account_manager_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      account_manager_m.EditAccount(userinput);
      account_manager_m.SaveAccountList(currentfileid_m);
      std::cout << std::endl;
      break;
    } else {
      std::cout << "\nPlease re-enter the name of the account you would "
                   "like to edit"
                << std::endl;
    }
  }
}

/* Delete Account */
/* Presents the user with the option of deleting an Account that they have saved
 */
void AmphoraInterface::DeleteAccountSubmenu() {
  std::string userinput;
  std::string f = "long";
  std::string s = "test";
  account_manager_m.ViewAccountList(f, s);

  while (1) {
    std::cout << "\nPlease type in the name of the account you would like "
                 "to delete"
              << std::endl;
    getline(std::cin, userinput);

    if (userinput == "~") {
      return;
    } else if (account_manager_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      AmphoraInterface::VerifyDeleteAccountPopup(userinput);
      break;
    } else {
      std::cout << "\nPlease re-enter the name of the account you would like "
                   "to delete"
                << std::endl;
    }
  }
}

// user should be able select the account they want to view.
/* View Accounts */
/* Displays Accounts that the currently logged in User has saved */
void AmphoraInterface::ViewAccountsSubmenu() {
  std::string viewstyle = "long";
  std::string sortchoice = "test";
  account_manager_m.ViewAccountList(viewstyle, sortchoice);
}

/* Options */
/* (1) Encryption Settings
   (2)
   */
void AmphoraInterface::OptionsSubmenu() {
  // stuff
}

/* Verify Add Account Popup */
/* Asks user to verify their entry */
void AmphoraInterface::VerifyAddAccountPopup(const std::string &accountname) {
  std::string submenu;
  while (1) {
    std::cout << "\nIs the information correct?\n";
    account_manager_m.ViewAccount(accountname);
    std::cout << "\n(1): Save account\n(2): Edit account\n(3): Return to Main "
                 "Menu without saving\n";
    getline(std::cin, submenu);

    if (submenu == "1") {
      std::cout << "Saving account..." << std::endl;
      account_manager_m.SaveAccountList(currentfileid_m);
      break;
    }

    // edit new account before saving
    else if (submenu == "2") {
      std::cout << "\n****** Editing account..." << std::endl;
      account_manager_m.EditAccount(accountname);
    }

    // return to mainmenu without creating/saving new account
    else if (submenu == "3") {
      std::cout << "\nAccount not saved.\n";
      std::cout << "\nReturning to Main Menu...\n";
      account_manager_m.DeleteAccount(accountname);
      break;
    }
  }
}

/* Verify Delete Account Popup */
/* Asks user to verify their delete account entry */
void AmphoraInterface::VerifyDeleteAccountPopup(
    const std::string &accountname) {
  std::string userinput;
  std::cout << "\nAre you sure you want to delete this account (y/n)?"
            << std::endl;
  std::cout << "*** " << accountname << " ***" << std::endl;
  getline(std::cin, userinput);
  if (userinput == "y" || userinput == "Y") {
    account_manager_m.DeleteAccount(accountname);
    account_manager_m.SaveAccountList(currentfileid_m);
    std::cout << "Account deleted!" << std::endl;
  } else if (userinput == "n" || userinput == "N") {
    return;
  }
}
