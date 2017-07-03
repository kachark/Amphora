
#include "account_manager.hpp"
#include <iostream>
#include <vector>

namespace AmphoraBackend
{
  AccountManager::AccountManager()
  {
    // TEST OF ENCRYPTION ON HASHING
    std::string test = "masterpassword";
    CryptoPP::SecByteBlock somekey = crypto_util_m.GetPBKDF2(test);

    CryptoPP::SecByteBlock iv = crypto_util_m.GetPseudoRNG(16);

    std::string ciphertext;
    ciphertext = crypto_util_m.Encrypt(somekey, iv);

    std::string decrypted;
    decrypted = crypto_util_m.Decrypt(ciphertext, somekey, iv);

    // CryptoPP::SecByteBlock salttest = crypto_util_m.GetPseudoRNG(32);
    // std::string salt = crypto_util_m.SecByteBlockToString(salttest);
    // std::cout << "Salt: " << salt << std::endl;
  }


  // initializes temp account and adds to accountdata_m
  // viewaccount and editaccount will check accountdata_m for the name of tempAccount (similar to how it will check any other account
  // saveaccountlist will serialize the current buffer accountdata_m
  // tempAccount will be reset to NULL
  void AccountManager::AddAccount(const std::string &name, const std::string &purpose, const std::string &username, const std::string &password)
  {
    std::string date = amphora_util_m.CurrentDate();

    tempAccount.set_name(name);
    tempAccount.set_purpose(purpose);
    tempAccount.set_username(username);
    tempAccount.set_password(password);
    tempAccount.set_datecreated(date);
    tempAccount.set_datemodified(date);

    // store temporary new account in map
    accountdata_m.insert(std::make_pair(name, tempAccount));
  }

  // edit account information
  // make sure to ask user to enter password twice to make sure they entered correctly
  // TODO
  // should pickup the account and pass it along to the UI
  // return desired Account obj
  Account AccountManager::EditAccount(const std::string &accountname)
  {
    Account &account = accountdata_m[accountname];

    return account;

    // std::string user;
    // while (1) {
    //   AmphoraBackend::ViewAccount(accountname);
    //   std::cout << "\nWhat would you like to edit?\n(1): Name\t(2): Purpose\t(3): Username\t(4): Password\t(5): Finish edit and save\n";
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

  void AccountManager::DeleteAccount(const std::string &accountname)
  {
    accountdata_m.erase(accountname);
  }

  // searches accountlist for account given accountname
  // confirms if account is found
  bool AccountManager::FindAccount(const std::string &accountname)
  {
    if (accountdata_m.find(accountname) != accountdata_m.end()) {
      return true; // found
    } else { // account key not found
      return false;
    }
  }

  // TODO remove from backend
  // the UI should handle this! ui call FindAccount -> return desired Account obj GetAccount
  // displays acccount info in nice format
  void AccountManager::ViewAccount(const std::string &accountname)
  {
    const Account &account = accountdata_m[accountname];
    std::cout << "Name: \t\t" << account.get_name() << std::endl;
    std::cout << "Purpose: \t" << account.get_purpose() << std::endl;
    std::cout << "Username: \t" << account.get_username() << std::endl;
    std::cout << "Password: \t" << account.get_password() << std::endl;
    std::cout << "Date created: \t" << account.get_datecreated() << std::endl;
    std::cout << "Date modified: \t" << account.get_datemodified() << std::endl;
  }

  // loads account using cereal
  void AccountManager::LoadAccountList()
  {
    // TODO - ensure file exists!
    std::string filename = "vault.xml";
    std::vector<Account> accountvector;
    amphora_util_m.LoadFromFile<Account>(filename, accountvector);
    for (auto account : accountvector) {
      accountdata_m.insert(std::make_pair(account.get_name(), account));
    }
  }

  // saves account using cereal serialization library
  // will create new file or overwrite existing file
  void AccountManager::SaveAccountList()
  {

    // TODO - filename should be a constant throughout the program
    std::string filename = "vault.xml";
    std::size_t num_saved;
    std::cout << "NUMBER BEING SAVED" << accountdata_m.size() << std::endl;
    std::vector<Account> accountvector;
    for (auto account : accountdata_m) {
      accountvector.push_back(account.second);
    }
    amphora_util_m.SaveToFile<Account>(filename, accountvector);
  }

  //TODO
  // move to amphorainterface
  void AccountManager::ViewAccountList(const std::string &format, const std::string &sortstyle)
  {
    //format "short" displays up to the 5 most recent accounts saved in the vault
    //format "long" displays all of the accounts in a given sort - default sort is by acct purpose

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

  void AccountManager::ClearTempAccount()
  {
    // reset temporary account object
    tempAccount.set_name("");
    tempAccount.set_purpose("");
    tempAccount.set_username("");
    tempAccount.set_password("");
    tempAccount.set_datecreated("");
    tempAccount.set_datemodified("");
  }
}