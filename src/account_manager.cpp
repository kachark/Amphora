
#include "../include/account_manager.hpp"
#include <fstream>
#include <iostream>
#include <vector>

namespace AmphoraBackend {
AccountManager::AccountManager() {}

// initializes temp account and adds to accountdata_m
// viewaccount and editaccount will check accountdata_m for the name of
// tempAccount (similar to how it will check any other account
// saveaccountlist will serialize the current buffer accountdata_m
// tempAccount will be reset to NULL
void AccountManager::AddAccount(const std::string &name,
                                const std::string &purpose,
                                const std::string &username,
                                const std::string &password) {
  std::string date = amphora_util_m.CurrentDate();

  tempaccount_m.set_name(name);
  tempaccount_m.set_purpose(purpose);
  tempaccount_m.set_username(username);
  tempaccount_m.set_password(password);
  tempaccount_m.set_datecreated(date);
  tempaccount_m.set_datemodified(date);

  // store temporary new account in map
  accountdata_m.insert(std::make_pair(name, tempaccount_m));
  tempaccount_m.clear();
}

// edit account information
// make sure to ask user to enter password twice to make sure they entered
// correctly
// TODO
// should pickup the account and pass it along to the UI
// return desired Account obj
Account AccountManager::EditAccount(const std::string &accountname) {
  Account &account = accountdata_m[accountname];

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

void AccountManager::DeleteAccount(const std::string &accountname) {
  accountdata_m.erase(accountname);
}

// searches accountlist for account given accountname
// confirms if account is found
bool AccountManager::FindAccount(const std::string &accountname) {
  if (accountdata_m.find(accountname) != accountdata_m.end()) {
    return true; // found
  } else {       // account key not found
    return false;
  }
}

// TODO remove from backend
// the UI should handle this! ui call FindAccount -> return desired Account obj
// GetAccount
// displays acccount info in nice format
void AccountManager::ViewAccount(const std::string &accountname) {
  const Account &account = accountdata_m[accountname];
  std::cout << "Name: \t\t" << account.get_name() << std::endl;
  std::cout << "Purpose: \t" << account.get_purpose() << std::endl;
  std::cout << "Username: \t" << account.get_username() << std::endl;
  std::cout << "Password: \t" << account.get_password() << std::endl;
  std::cout << "Date created: \t" << account.get_datecreated() << std::endl;
  std::cout << "Date modified: \t" << account.get_datemodified() << std::endl;
}

// loads account using cereal
bool AccountManager::LoadAccountList(const std::string &fileid) {
  bool loadstatus;
  std::string filename = "../data/" + fileid + ".xml";
  std::cout << filename << std::endl;
  std::vector<Account> accountvector;
  if (amphora_util_m.FindFile(filename)) {  // check if file exists in directory
    std::cout << "File found" << std::endl; // debug
    loadstatus = amphora_util_m.LoadFromFile<Account>(filename, accountvector);
    if (loadstatus) { // if load success + check file -> return true
      // populate memory
      for (auto account : accountvector) {
        accountdata_m.insert(std::make_pair(account.get_name(), account));
      }
      return 1;
    }
  }
  return 0;
}

// saves account using cereal serialization library
// will create new file or overwrite existing file
bool AccountManager::SaveAccountList(const std::string &fileid) {
  bool filefound, savestatus;
  std::string filename = "../data/" + fileid + ".xml";
  std::cout << filename << std::endl;
  std::cout << "NUMBER BEING SAVED" << accountdata_m.size() << std::endl;
  std::vector<Account> accountvector;
  // prepare vector of objects to serialize
  for (auto account : accountdata_m) {
    accountvector.push_back(account.second);
  }
  filefound = amphora_util_m.FindFile(filename);
  while (!filefound) {
    // create file if not found/doesn't exist
    std::fstream fs;
    fs.open(filename.data(), std::ios::out);
    fs.close();
    filefound = amphora_util_m.FindFile(filename);
  }
  if (filefound) {
    std::cout << "File found" << std::endl; // debug
    savestatus = amphora_util_m.SaveToFile<Account>(filename, accountvector);
    if (savestatus) { // if save success + check file -> return true
      return 1;
    }
  }
  return 0;
}

// TODO
// move to amphorainterface?
void AccountManager::ViewAccountList(const std::string &format,
                                     const std::string &sortstyle) {
  // format "short" displays up to the 5 most recent accounts saved in the vault
  // format "long" displays all of the accounts in a given sort - default sort
  // is by acct purpose

  std::cout << std::endl << "Your Saved Accounts:" << std::endl;
  std::vector<std::string> accountnamelist;
  std::size_t largestaccountname = 0;
  // sort accountlist_m before displaying

  // get names from account objects
  if (format == "long") {
    for (auto account : accountdata_m) {
      std::string accountname = account.second.get_name();
      accountnamelist.push_back(accountname);
    }
  }

  // displays first 5 accounts stored in accountlist_m
  // sorts by most recently modified!!
  else if (format == "short") {
    int i = 0;
    for (auto account : accountdata_m) {
      if (i < 5) {
        std::string accountname = account.second.get_name();
        accountnamelist.push_back(accountname);
      }
      ++i;
    }
  }
  amphora_util_m.PrettyTable(accountnamelist);
}
}
