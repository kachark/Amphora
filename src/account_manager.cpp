
#include "../include/account_manager.hpp"
#include <iostream>
#include <vector>

namespace AmphoraBackend {
AccountManager::AccountManager() {
  std::string plaintext = "encrypt this";

  std::string masterpassword = "hello world";
  std::string anothermasterpw = "hi";
  // // TEST OF ENCRYPTION ON HASHING
  CryptoPP::SecByteBlock somekey = crypto_util_m.GetPBKDF2(masterpassword);
  CryptoPP::SecByteBlock somekey2 = crypto_util_m.GetPBKDF2(anothermasterpw);
  // // need to convert key to string to save

  CryptoPP::SecByteBlock iv = crypto_util_m.GetPseudoRNG(16);
  CryptoPP::SecByteBlock iv2 = crypto_util_m.GetPseudoRNG(16);
  // // need to convert iv to string to save

  std::string ciphertext;
  std::string ciphertext2;
  ciphertext = crypto_util_m.Encrypt(plaintext, somekey, iv);
  ciphertext2 = crypto_util_m.Encrypt(plaintext, somekey2, iv2);

  std::string decrypted;
  // TEST: decrypt using wrong key and/or iv for a given ciphertext
  // exception caught inside Decrypt
  decrypted = crypto_util_m.Decrypt(ciphertext2, somekey, iv2);
  // handle failed decryption (or encryption) for log in or accounts!
  if (decrypted.empty()) {
    std::cout << "BAD DECRYPTION" << std::endl;
  }

  // CryptoPP::SecByteBlock salttest = crypto_util_m.GetPseudoRNG(32);
  // std::string salt = crypto_util_m.SecByteBlockToString(salttest);
  // std::cout << "Salt: " << salt << std::endl;
}

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

  tempaccount.set_name(name);
  tempaccount.set_purpose(purpose);
  tempaccount.set_username(username);
  tempaccount.set_password(password);
  tempaccount.set_datecreated(date);
  tempaccount.set_datemodified(date);

  // store temporary new account in map
  accountdata_m.insert(std::make_pair(name, tempaccount));
  tempaccount.clear();
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
bool AccountManager::LoadAccountList() {
  bool loadstatus;
  std::string filename = "../data/vault.xml";
  std::vector<Account> accountvector;
  if (amphora_util_m.CheckFile(filename)) { // check if file exists in directory
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
bool AccountManager::SaveAccountList() {

  // TODO - filename should be a constant throughout the program
  bool savestatus;
  std::string filename = "../data/vault.xml";
  std::size_t num_saved;
  std::cout << "NUMBER BEING SAVED" << accountdata_m.size() << std::endl;
  std::vector<Account> accountvector;
  // prepare vector of objects to serialize
  for (auto account : accountdata_m) {
    accountvector.push_back(account.second);
  }
  if (amphora_util_m.CheckFile(filename)) {
    std::cout << "File found" << std::endl; // debug
    savestatus = amphora_util_m.SaveToFile<Account>(filename, accountvector);
    if (savestatus) { // if save success + check file -> return true
      return 1;
    }
  }
  return 0;
}

// TODO
// move to amphorainterface
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
