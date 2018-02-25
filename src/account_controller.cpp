
#include "account_controller.hpp"
#include <fstream>
#include <iostream>
#include <vector>

//AccountController::~AccountController() {
//}
//
//AccountController &AccountController::operator=(const AccountController &rhs) {
//  if (this != &rhs) {
//    tempaccount_m = rhs.tempaccount_m;
//    accountlist_m = rhs.accountlist_m;
//  }
//  return *this;
//}

void AccountController::set_user(const User &user) { account_owner_m = user; }

User AccountController::get_user() { return account_owner_m; }

/*initializes temp account and adds to accountlist_m
viewaccount and editaccount will check accountlist_m for the name of
tempAccount (similar to how it will check any other account
saveaccountlist will serialize the current buffer accountlist_m
tempAccount will be reset to NULL*/
void AccountController::AddAccount(const Account &account) {
  // store temporary new account in map
  accountlist_m.insert(std::make_pair(account.get_name(), account));
}

// edit account information
// make sure to ask user to enter password twice to make sure they entered
// correctly
// TODO
// should pickup the account and pass it along to the UI
// return desired Account obj
Account AccountController::EditAccount(const std::string &accountname) {
  Account & account = accountlist_m[accountname];

  return account;

  // std::string user;
  // while (1) {
  //   AmphoraBackend::ViewAccount(accountname);
  //   std::cout << "\nWhat would you like to edit?\n(1): Name\t(2):
  //   Purpose\t(3): Username\t(4): Password\t(5): Finish edit and save\n";
  //   getline(std::cin, user);

  //   if (user == "1") {
  //     std::cout << "Enter a name for this account:\t";
  //     getline(std::cin, user);
  //     account.set_name(user);
  //   }
  //   if (user == "2") {
  //     std::cout << "Enter the purpose of this account:\t";
  //     getline(std::cin, user);
  //     account.set_purpose(user);
  //   }
  //   if (user == "3") {
  //     std::cout << "Enter the username for this account:\t";
  //     getline(std::cin, user);
  //     account.set_username(user);
  //   }
  //   if (user == "4") {
  //     std::cout << "Enter the password for this account:\t";
  //     getline(std::cin, user);
  //     account.set_password(user);
  //   }
  //   if (user == "5") {
  //     std::cout << "****** Finished Editing... \n";
  //     break;
  //   }
  // }
}

void AccountController::DeleteAccount(const std::string &accountname) {
  accountlist_m.erase(accountname);
}

// searches accountlist for account given accountname
// returns true if found, false if not found
bool AccountController::FindAccount(const std::string &accountname) {
  if (accountlist_m.count(accountname)) {
    return true; // found
  } else {       // account key not found
    return false;
  }
}

// returns reference to Account
Account &AccountController::GetAccount(const std::string &accountname) {
  return accountlist_m[accountname];
}

// TODO p1-1 return account and let the cli handle printing
// TODO remove from backend?
// TODO decrypt username, password
// the UI should handle this! ui call FindAccount -> return desired Account
// obj GetAccount displays acccount info in nice format
//void AccountController::ViewAccount(const std::string &accountname,
//                                    Crypto &crypto, User &currentuser) {
//
//  const Account &account = accountlist_m[accountname];
//  std::string username_cipher = account.get_username();
//  // TODO
//  std::string iv1 = username_cipher; // extract iv1 from username
//  std::string password_cipher = account.get_password();
//  // TODO
//  std::string iv2 = password_cipher; // extract iv2 from password
//  std::string username = crypto_util_m.AES_GCM_Decrypt(
//      username_cipher, currentuser.get_password(), iv1);
//  std::string password = crypto_util_m.AES_GCM_Decrypt(
//      password_cipher, currentuser.get_password(), iv2);
//
//  std::cout << "Name: \t\t" << account.get_name() << std::endl;
//  std::cout << "Purpose: \t" << account.get_details() << std::endl;
//  std::cout << "Username: \t" << account.get_username() << std::endl;
//  std::cout << "Password: \t" << account.get_password() << std::endl;
//  std::cout << "Date created: \t" << account.get_datecreated() << std::endl;
//  std::cout << "Date modified: \t" << account.get_datemodified() << std::endl;
//}

// TODO put this in mediator!!
// loads account using cereal
bool AccountController::LoadAccountList(std::weak_ptr<AmphoraUtilities> wP_util, const std::string &filepath) {
  std::shared_ptr<AmphoraUtilities> sP_util = wP_util.lock();

  bool loadstatus;
//    std::string filename = "../data/user/" + fileid + ".xml";
  std::cout << filepath << std::endl;
  std::vector<Account> accountvector;
  if (sP_util) {
    if (sP_util->FindFile(filepath)) {            // check if file exists in directory
      std::cout << "File found" << std::endl; // debug
      loadstatus = sP_util->LoadVector<Account>(filepath, accountvector);
      if (loadstatus) { // if load success + check file ->
        return true;
        // populate memory
        for (auto account : accountvector) {
          accountlist_m.insert(std::make_pair(account.get_name(), account));
        }
        return 1;
      }
    }
    return false;
  } else { // no utility object
    return false;
  }
}

// saves account using cereal serialization library
// will create new file or overwrite existing file
bool AccountController::SaveAccountList(std::weak_ptr<AmphoraUtilities> wP_util, const std::string &filepath) {
  std::shared_ptr<AmphoraUtilities> sP_util = wP_util.lock();

  bool filefound, savestatus;
//    std::string filename = "../data/users/" + fileid + ".xml";
  std::cout << filepath << std::endl;
  std::cout << "NUMBER BEING SAVED" << accountlist_m.size() << std::endl;
  std::vector<Account> accountvector;
  // prepare vector of objects to serialize
  for (auto account : accountlist_m) {
    accountvector.push_back(account.second);
  }
  filefound = sP_util->FindFile(filepath);
  // TODO not finding the file and creating a new one
  if (!filefound) {
    std::cout << "DEBUG" << std::endl;
    // create file if not found/doesn't exist
    std::fstream fs;
    fs.open(filepath.data(), std::ios::out);
    fs.close();
    filefound = sP_util->FindFile(filepath);
  }
  if (filefound) {
    std::cout << "File found" << std::endl; // debug
    savestatus = sP_util->SaveVector<Account>(filepath, accountvector);
    if (savestatus) { // if save success + check file -> return true
      return true;
    }
  }
  return false;
}

// TODO
// move to amphorainterface?
void AccountController::ViewAccountList(const std::string &format,
                                        const std::string &sortstyle) {
  // format "short" displays up to the 5 most recent accounts saved in the
  // vault format "long" displays all of the accounts in a given sort -
  // default sort is by acct purpose

  std::cout << std::endl << "Your Saved Accounts:" << std::endl;
  std::vector<std::string> accountnamelist;
  std::size_t largestaccountname = 0;
  // sort accountlist_m before displaying

  // get names from account objects
  if (format == "long") {
    for (auto account : accountlist_m) {
      std::string accountname = account.second.get_name();
      accountnamelist.push_back(accountname);
    }
  }

    // displays first 5 accounts stored in accountlist_m
    // sorts by most recently modified!!
  else if (format == "short") {
    int i = 0;
    for (auto account : accountlist_m) {
      if (i < 5) {
        std::string accountname = account.second.get_name();
        accountnamelist.push_back(accountname);
      }
      ++i;
    }
  }
//    amphora_util_m.PrettyTable(accountnamelist);
}

/* Notify mediator of changes */
//void AccountController::Changed() {
//    mediator_m->ElementChanged(*this);
//}
