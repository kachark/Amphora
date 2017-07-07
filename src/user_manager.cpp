

#include "user_manager.hpp"
#include <iostream>
#include <vector>

namespace AmphoraBackend
{

  UserManager::UserManager()
  {

  }


  bool UserManager::CheckUser(const std::string &username, const std::string &password)
  {
    // return 0 if no match, 1 if match
    return 0;

  }

  //TODO
  // what is the correct way to identify a user? ie. not by username

  // searches accountlist for account given accountname
  // confirms if account is found
  bool UserManager::FindAccount(const std::string &username)
  {
    if (userdata_m.find(username) != userdata_m.end()) {
      return true; // found
    } else { // account key not found
      return false;
    }
  }

  // loads account using cereal
  bool UserManager::LoadUserList()
  {
    // TODO - ensure file exists!
    bool loadstatus;
    std::string filename = "../data/vault2.xml";
    std::vector<User> uservector;
    if (amphora_util_m.CheckFile(filename)) { // check if file exists in directory
      std::cout << "File found" << std::endl; // debug
      loadstatus = amphora_util_m.LoadFromFile<User>(filename, uservector);
      if (loadstatus) { // if load success + check file -> return true
        // populate memory
        for (auto user : uservector) {
          userdata_m.insert(std::make_pair(user.get_username(), user));
        }
        return 1;
      }
    }
    return 0;
  }

  // saves account using cereal serialization library
  // will create new file or overwrite existing file
  bool UserManager::SaveUserList()
  {

    // TODO - filename should be a constant throughout the program
    bool savestatus;
    std::string filename = "../data/vault2.xml";
    std::size_t num_saved;
    std::cout << "NUMBER BEING SAVED" << userdata_m.size() << std::endl;
    std::vector<User> uservector;
    // prepare vector of objects to serialize
    for (auto user : userdata_m) {
      uservector.push_back(user.second);
    }
    if (amphora_util_m.CheckFile(filename)) {
      std::cout << "File found" << std::endl; // debug
      savestatus = amphora_util_m.SaveToFile<User>(filename, uservector);
      if (savestatus) { // if save success + check file -> return true
        return 1;
      }
    }
    return 0;
  }


  // // initializes temp account and adds to accountdata_m
  // // viewaccount and editaccount will check accountdata_m for the name of tempAccount (similar to how it will check any other account
  // // saveaccountlist will serialize the current buffer accountdata_m
  // // tempAccount will be reset to NULL
  void UserManager::AddUser(const std::string &username, const std::string &password)
  {
    std::string date = amphora_util_m.CurrentDate();

    tempuser.set_username(username);
    tempuser.set_password(password);
    tempuser.set_datecreated(date);
    tempuser.set_datemodified(date);

    // store temporary new user in map
    userdata_m.insert(std::make_pair(username, tempuser));
    tempuser.clear();
  }

  // // edit account information
  // // make sure to ask user to enter password twice to make sure they entered correctly
  // // TODO
  // // should pickup the account and pass it along to the UI
  // // return desired Account obj
  // Account UserManager::EditAccount(const std::string &accountname)
  // {
  //   Account &account = accountdata_m[accountname];

  //   return account;

  //   // std::string user;
  //   // while (1) {
  //   //   AmphoraBackend::ViewAccount(accountname);
  //   //   std::cout << "\nWhat would you like to edit?\n(1): Name\t(2): Purpose\t(3): Username\t(4): Password\t(5): Finish edit and save\n";
  //   //   getline(std::cin, user);

  //   //   if (user == "1") {
  //   //     std::cout << "Enter a name for this account:\t";
  //   //     getline(std::cin, user);
  //   //     account.set_name(user);
  //   //   }
  //   //   if (user == "2") {
  //   //     std::cout << "Enter the purpose of this account:\t";
  //   //     getline(std::cin, user);
  //   //     account.set_purpose(user);
  //   //   }
  //   //   if (user == "3") {
  //   //     std::cout << "Enter the username for this account:\t";
  //   //     getline(std::cin, user);
  //   //     account.set_username(user);
  //   //   }
  //   //   if (user == "4") {
  //   //     std::cout << "Enter the password for this account:\t";
  //   //     getline(std::cin, user);
  //   //     account.set_password(user);
  //   //   }
  //   //   if (user == "5") {
  //   //     std::cout << "****** Finished Editing... \n";
  //   //     break;
  //   //   }
  //   // }
  // }

  // void UserManager::DeleteAccount(const std::string &accountname)
  // {
  //   accountdata_m.erase(accountname);
  // }


  // // TODO remove from backend
  // // the UI should handle this! ui call FindAccount -> return desired Account obj GetAccount
  // // displays acccount info in nice format
  // void UserManager::ViewAccount(const std::string &accountname)
  // {
  //   const Account &account = accountdata_m[accountname];
  //   std::cout << "Name: \t\t" << account.get_name() << std::endl;
  //   std::cout << "Purpose: \t" << account.get_purpose() << std::endl;
  //   std::cout << "Username: \t" << account.get_username() << std::endl;
  //   std::cout << "Password: \t" << account.get_password() << std::endl;
  //   std::cout << "Date created: \t" << account.get_datecreated() << std::endl;
  //   std::cout << "Date modified: \t" << account.get_datemodified() << std::endl;
  // }

  // // loads account using cereal
  // void UserManager::LoadAccountList()
  // {
  //   // might be better to have filename as an arg?
  //   std::string filename = "vault.xml";
  //   // check if filename is in the pwd
  //   std::size_t num_saved;
  //   {
  //     // open stream
  //     // HOW TO CHECK IF FILENAME EXISTS OR NOT?
  //     // IF NOT: create a new vault.xml (default vault filename)
  //     // IF exists, but file is empty: terminate load process??
  //     std::ifstream is(filename);
  //     cereal::XMLInputArchive archive(is);
  //     // call archive and get number of saved accounts from archive's first index.
  //     archive( num_saved );
  //     // loop and call archive for the number of saved accounts, to ensure every account is retrieved.
  //     for ( auto i = 0; i < num_saved; ++i ) {
  //       Account temp;
  //       archive( temp );
  //       // accountlist_m.push_back(temp);
  //       accountdata_m.insert(std::make_pair(temp.get_name(), temp));
  //     }
  //       std::cout << "DEBUG: num_saved = " << num_saved << std::endl;
  //   }

  // }

  // // saves account using cereal serialization library
  // void UserManager::SaveAccountList()
  // {

  //   std::string savedaccount = "vault.xml";
  //   std::size_t num_saved;
  //   // std::cout << "NUMBER BEING SAVED" << accountlist_m.size() << std::endl;
  //   std::cout << "NUMBER BEING SAVED" << accountdata_m.size() << std::endl;
  //   {
  //     std::ofstream file( savedaccount );
  //     cereal::XMLOutputArchive archive( file );

  //     num_saved = accountdata_m.size();
  //     archive(num_saved);

  //     for (auto account : accountdata_m) {
  //       archive(account.second);
  //     }
  //  } // when archive goes out of scope it is guaranteed to have flushed its
  //     // contents to its stream
  // }

  // void UserManager::ViewAccountList(const std::string &format, const std::string &sortstyle)
  // {
  //   //format "short" displays up to the 5 most recent accounts saved in the vault
  //   //format "long" displays all of the accounts in a given sort - default sort is by acct purpose

  //   std::cout << std::endl << "Your Saved Accounts:" << std::endl;
  //   std::vector<std::string> accountnamelist;
  //   std::size_t largestaccountname = 0;
  //   // sort accountlist_m before displaying

  //   // get names from account objects
  //   if (format == "long") {
  //     for (auto account : accountdata_m) {
  //       std::string accountname = account.second.get_name();
  //       accountnamelist.push_back(accountname);
  //     }
  //   }

  //   // displays first 5 accounts stored in accountlist_m
  //   // sorts by most recently modified!!
  //   else if (format == "short") {
  //     int i = 0;
  //     for (auto account : accountdata_m) {
  //       if (i < 5) {
  //         std::string accountname = account.second.get_name();
  //         accountnamelist.push_back(accountname);
  //       }
  //       ++i;
  //     }
  //   }
  //   amphora_util_m.PrettyTable(accountnamelist);
  // }


}
