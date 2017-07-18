

#include "../include/user_manager.hpp"
#include <iostream>
#include <vector>

namespace AmphoraBackend {

UserManager::UserManager() {}

// TODO
// verifies user as being registered in system
bool UserManager::VerifyUser(const std::string &username,
                             const std::string &password,
                             CryptoManager &crypto_manager) {
  auto userfound = FindUser(username);
  if (!userfound) {
    std::cout << "User not found in userdata" << std::endl;
  } else {
    // compare this user's pw/key with what was passed into this function
    User loggedin = userdata_m[username];
    // access this user's crypto settings
    CryptoDB cryptodb = crypto_manager.GetCryptoDB(username);
    // std::size_t saltsize = cryptodb.get_saltsize();
    std::string saltstr = cryptodb.get_salt();
    CryptoPP::SecByteBlock salt = crypto_util_m.StringToSecByteBlock(saltstr);
    std::size_t keysize = cryptodb.get_keysize();
    unsigned int iterations = cryptodb.get_iterations();

    CryptoPP::SecByteBlock masterkey =
        crypto_util_m.GetPBKDF2(iterations, salt, keysize, password);
    std::string hashedpassword = crypto_util_m.SecByteBlockToString(masterkey);
    // TODO
    std::cout << "YOUR PBKDF2: " << hashedpassword << std::endl; // debug
    std::cout << "THE USERS PBKDF2: " << password << std::endl;  // debug
    if (hashedpassword == loggedin.get_password()) {
      return 1;
    }
  }
  return 0;
}

// searches accountlist for account given accountname
// confirms if account is found
bool UserManager::FindUser(const std::string &username) {
  if (userdata_m.count(
          username)) { // assumes userdata_m is map and all items are unique
    return true;       // found
  } else {             // account key not found
    return false;
  }
}

// loads account using cereal
bool UserManager::LoadUserList() {
  // TODO - ensure file exists!
  bool loadstatus;
  std::string filename = "../data/users/users.xml";
  std::vector<User> uservector;
  if (amphora_util_m.FindFile(filename)) {  // check if file exists in directory
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
bool UserManager::SaveUserList() {

  // TODO - filename should be a constant throughout the program
  bool savestatus;
  std::string filename = "../data/users/users.xml";
  std::cout << "NUMBER BEING SAVED" << userdata_m.size() << std::endl;
  std::vector<User> uservector;
  // prepare vector of objects to serialize
  for (auto user : userdata_m) {
    uservector.push_back(user.second);
  }
  if (amphora_util_m.FindFile(filename)) {
    std::cout << "File found" << std::endl; // debug
    savestatus = amphora_util_m.SaveToFile<User>(filename, uservector);
    if (savestatus) { // if save success + check file -> return true
      return 1;
    }
  }
  return 0;
}

// // initializes temp account and adds to accountdata_m
// // viewaccount and editaccount will check accountdata_m for the name of
// tempAccount (similar to how it will check any other account
// // saveaccountlist will serialize the current buffer accountdata_m
// // tempAccount will be reset to NULL
void UserManager::AddUser(const std::string &username,
                          const std::string &password,
                          const std::string &fileid) {
  std::string date = amphora_util_m.CurrentDate();

  tempuser_m.set_username(username);
  tempuser_m.set_password(password);
  tempuser_m.set_datecreated(date);
  tempuser_m.set_datemodified(date);
  tempuser_m.set_accountfileid(fileid);

  // store temporary new user in map
  userdata_m.insert(std::make_pair(username, tempuser_m));
  // clear temporary user
  tempuser_m.clear();
}

// // edit account information
// // make sure to ask user to enter password twice to make sure they entered
// correctly
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
//   //   std::cout << "\nWhat would you like to edit?\n(1): Name\t(2):
//   Purpose\t(3): Username\t(4): Password\t(5): Finish edit and save\n";
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
// // the UI should handle this! ui call FindAccount -> return desired Account
// obj GetAccount
// // displays acccount info in nice format
// void UserManager::ViewAccount(const std::string &accountname)
// {
//   const Account &account = accountdata_m[accountname];
//   std::cout << "Name: \t\t" << account.get_name() << std::endl;
//   std::cout << "Purpose: \t" << account.get_purpose() << std::endl;
//   std::cout << "Username: \t" << account.get_username() << std::endl;
//   std::cout << "Password: \t" << account.get_password() << std::endl;
//   std::cout << "Date created: \t" << account.get_datecreated() <<
//   std::endl;
//   std::cout << "Date modified: \t" << account.get_datemodified() <<
//   std::endl;
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
//     // call archive and get number of saved accounts from archive's first
//     index.
//     archive( num_saved );
//     // loop and call archive for the number of saved accounts, to ensure
//     every account is retrieved.
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
//   // std::cout << "NUMBER BEING SAVED" << accountlist_m.size() <<
//   std::endl;
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

// void UserManager::ViewAccountList(const std::string &format, const
// std::string &sortstyle)
// {
//   //format "short" displays up to the 5 most recent accounts saved in the
//   vault
//   //format "long" displays all of the accounts in a given sort - default
//   sort
//   is by acct purpose

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
