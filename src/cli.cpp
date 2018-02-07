

#include "cli.hpp"
#include "account_controller.hpp"
#include "crypto_controller.hpp"
#include "user_controller.hpp"
#include <iostream>

/* Amphora Interface Constructor */
AmphoraInterface::AmphoraInterface() { exit_flag_m = false; }

/* Start Amphora Interface */
void AmphoraInterface::Start() {
  std::cout << "Welcome to AMPHORA" << std::endl;
  std::cout << "Press '~' at any time to return to the main menu" << std::endl;

  // TODO p1-1
  Setup();
  // LoadCryptoConfig();
  // LoadUserFile();
  LogIn();
  LoadAccountFile();
  MainMenu();
}

/* Setup Mediator */
void AmphoraInterface::Setup() {
  mediator_m = std::unique_ptr<AmphoraMediator>(new AmphoraMediator());
  mediator_m->Setup();
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
  while (attempts < MAXLOGINS_m) {
    std::cout << "LOG IN" << std::endl;
    std::cout << "\n(1): Log In\n(2): Register new user\n(~): Quit"
              << std::endl;
    getline(std::cin, input);

    if (input == "~") {
      exit_flag_m = true;
      return;
    } else if (input == "1") {
      attempts++;

      // TODO p1-7 mask password and secure input
      // TODO p1-1
      std::cout << "Username: ";
      // username = AmphoraInterface::SecureInput()
      getline(std::cin, username);
      std::cout << "Password: ";
      // password = AmphoraInterface::SecureInput()
      getline(std::cin, password);

      // TODO p1-1
      // move VerifyUser into mediator
      bool verified =
          user_controller_m.VerifyUser(username, password, crypto_controller_m);
      // keep here
      if (!verified) {
        std::cout << "Your username or password are not recognized! Please "
                     "reenter or register. "
                  << std::endl;
      } else if (verified) { // logged in!
        std::cout << "Logged In!" << std::endl;
        // mediator_m->AddUser(username);

        // TODO p1-1
        // all of these lines, inside mediator
        // currentuser_m = user_controller_m.get_user(username);
        // crypto_m =
        //     crypto_controller_m.get_crypto(currentuser_m.get_crypto_id());
        // currentacctid_m = currentuser_m.get_account_file();
        break;
      }

    } else if (input == "2") {
      RegisterUser();
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

    // TODO p1-7
    // username = AmphoraInterface::SecureInput()
    std::cout << "Username: ";
    getline(std::cin, username);
    std::cout << "Password: ";
    getline(std::cin, password);
    std::cout << "Confirm password: ";
    getline(std::cin, confirmedpw);

    // TODO p1-1
    // check username against database
    bool usercollision = user_controller_m.FindUser(username);
    if (usercollision) {
      std::cout
          << "The username you entered is taken. Please enter another name"
          << std::endl;
    }

    // TODO p1-6 correct string comparison
    if (password != confirmedpw) {
      std::cout << "Please ensure your password is correctly entered"
                << std::endl;
    } else if ((usercollision == false) &&
               (password == confirmedpw)) { // register user

      // TODO p1-1
      user_controller_m.AddUser(username, password, crypto_controller_m);
      user_controller_m.SaveUserList();
      currentuser_m = user_controller_m.get_user(username);

      // add current user fileid to amphora interface to access their accounts
      // file
      currentacctid_m = currentuser_m.get_account_file();
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
      AddAccountSubmenu();
    }

    // edit existing account
    else if (userinput == "2") { // edit account
      EditAccountSubmenu();
    }

    // delete account
    else if (userinput == "3") {
      // go into the xml file and delete the necessary index
      DeleteAccountSubmenu();
    }

    else if (userinput == "4") {
      ViewAccountsSubmenu();
    }

    // TODO
    // config file for encryption settings - when it's changed from 'default',
    // name it the username
    // edit user settings - password
    // Advanced optios (TBD)
    else if (userinput == "5") {
      // choose Encryption options, fingerprint scanner support, secure
      // password
      // generator etc.
      // cli::advanced_options();
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
  bool loadusers = user_controller_m.LoadUserList();
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
        RegisterUser();
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
void AmphoraInterface::LoadCryptoConfig() {
  if (exit_flag_m == true) {
    return;
  }
  bool loaded = crypto_controller_m.LoadCrypto();
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
    unsigned int iterations = 1000000;
    crypto_controller_m.AddCrypto("default", saltsize, ivsize, keysize,
                                  iterations);
    bool saved = crypto_controller_m.SaveCrypto();
  }
}

/* Load Account File */
/* Loads Account File for the currently logged in User */
void AmphoraInterface::LoadAccountFile() {
  if (exit_flag_m == true) {
    return;
  }

  bool loadaccounts = account_controller_m.LoadAccountList(currentacctid_m);
  if (loadaccounts) {
    std::cout << "Accounts loaded" << std::endl;
  } else if (!loadaccounts) {
    std::cout << "LOAD FAILED" << std::endl;
    // cli::AddAccountSubmenu();
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
    } else if (account_controller_m.FindAccount(name)) {
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

  account_controller_m.AddAccount(name, purpose, username, password, crypto_m,
                                  currentuser_m);
  // this needs to change
  VerifyAddAccountPopup(name);
}

// TODO
/* Edit Account */
/* Presents the user with the option of editing Accounts that they have saved */
void AmphoraInterface::EditAccountSubmenu() {
  std::string userinput;
  std::string f = "long";
  std::string s = "test";
  account_controller_m.ViewAccountList(f, s);

  while (1) {
    std::cout
        << "\nPlease type in the name of the account you would like to edit"
        << std::endl;
    getline(std::cin, userinput);

    if (userinput == "~") {
      return;
    } else if (account_controller_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      account_controller_m.EditAccount(userinput);
      account_controller_m.SaveAccountList(currentacctid_m);
      std::cout << std::endl;
      break;
    } else {
      std::cout << "\nPlease re-enter the name of the account you would "
                   "like to edit"
                << std::endl;
    }
  }
}

// TODO
/* Delete Account */
/* Presents the user with the option of deleting an Account that they have saved
 */
void AmphoraInterface::DeleteAccountSubmenu() {
  std::string userinput;
  std::string f = "long";
  std::string s = "test";
  account_controller_m.ViewAccountList(f, s);

  while (1) {
    std::cout << "\nPlease type in the name of the account you would like "
                 "to delete"
              << std::endl;
    getline(std::cin, userinput);

    if (userinput == "~") {
      return;
    } else if (account_controller_m.FindAccount(userinput)) {
      std::cout << "Account Found!" << std::endl;
      VerifyDeleteAccountPopup(userinput);
      break;
    } else {
      std::cout << "\nPlease re-enter the name of the account you would like "
                   "to delete"
                << std::endl;
    }
  }
}

// TODO
// user should be able select the account they want to view.
/* View Accounts */
/* Displays Accounts that the currently logged in User has saved */
void AmphoraInterface::ViewAccountsSubmenu() {
  std::string viewstyle = "long";
  std::string sortchoice = "test";
  account_controller_m.ViewAccountList(viewstyle, sortchoice);
}

// TODO
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
    account_controller_m.ViewAccount(accountname, crypto_m, currentuser_m);
    std::cout << "\n(1): Save account\n(2): Edit account\n(3): Return to Main "
                 "Menu without saving\n";
    getline(std::cin, submenu);

    if (submenu == "1") {
      std::cout << "Saving account..." << std::endl;
      std::cout << "currentacctid_m: " << currentacctid_m << std::endl;
      account_controller_m.SaveAccountList(currentacctid_m);
      break;
    }

    // edit new account before saving
    else if (submenu == "2") {
      std::cout << "\n****** Editing account..." << std::endl;
      account_controller_m.EditAccount(accountname);
    }

    // return to mainmenu without creating/saving new account
    else if (submenu == "3") {
      std::cout << "\nAccount not saved.\n";
      std::cout << "\nReturning to Main Menu...\n";
      account_controller_m.DeleteAccount(accountname);
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
    account_controller_m.DeleteAccount(accountname);
    account_controller_m.SaveAccountList(currentacctid_m);
    std::cout << "Account deleted!" << std::endl;
  } else if (userinput == "n" || userinput == "N") {
    return;
  }
}
