

#include "user_controller.hpp"
#include "crypto.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using amphora::internal::Crypto;
using amphora::internal::User;

namespace amphora {
namespace core {

UserController::UserController() {}

void UserController::AddUser(const std::string &username,
                             const std::string &password,
                             CryptoController &crypto_controller) {

  std::string date = amphora_util_m.CurrentDate();

  // generate fileid for new User to create/manage Accounts
  internal::Crypto defaultcrypto = crypto_controller.get_crypto("default");
  unsigned int iterations = defaultcrypto.get_hmac_iterations();
  std::string accountfileid = crypto_util_m.AES_PRNG(3);
  std::string salt = crypto_util_m.AES_PRNG(defaultcrypto.get_saltsize());
  std::size_t keysize = defaultcrypto.get_keysize();
  std::string hashedpassword =
      crypto_util_m.PBKDF2(iterations, salt, keysize, password);

  tempuser_m.set_username(username);
  tempuser_m.set_password(hashedpassword);
  tempuser_m.set_datecreated(date);
  tempuser_m.set_datemodified(date);
  tempuser_m.set_accountfileid(accountfileid);
  tempuser_m.set_cryptoname("default");
  tempuser_m.set_salt(salt);

  // store temporary new user in map
  userlist_m.insert(std::make_pair(username, tempuser_m));
  // clear temporary user
  tempuser_m.clear();
}

// verifies provided username and password as being registered in system
bool UserController::VerifyUser(const std::string &username,
                                const std::string &password,
                                CryptoController &crypto_controller) {
  bool userfound = FindUser(username);
  if (!userfound) {
    std::cout << "User not found in userdata" << std::endl;
  } else { // username in database, now verify the password
    // compare this user's pw/key with what was passed into this function
    User loggedin = userlist_m[username];
    // access this user's crypto settings
    internal::Crypto crypto =
        crypto_controller.get_crypto(loggedin.get_cryptoname());
    // std::size_t saltsize = cryptodb.get_saltsize();
    std::string salt = loggedin.get_salt();
    std::size_t keysize = crypto.get_keysize();
    unsigned int iterations = crypto.get_hmac_iterations();
    std::string masterkey =
        crypto_util_m.PBKDF2(iterations, salt, keysize, password);

    std::cout << masterkey << std::endl;
    std::cout << loggedin.get_password() << std::endl;

    // if (masterkey == loggedin.get_password()) {
    // if (masterkey.compare(loggedin.get_password())) {
    if (std::lexicographical_compare(masterkey.begin(), masterkey.end(),
                                     loggedin.get_password().begin(),
                                     loggedin.get_password().end())) {
      return 1;
    }
  }
  return 0;
} // namespace core

// searches accountlist for account given accountname
// confirms if account is found
bool UserController::FindUser(const std::string &username) {
  // assumes userlist_m is map and all items are unique
  if (userlist_m.count(username)) {
    return true; // found
  } else {       // account key not found
    return false;
  }
}

// returns reference to User
User &UserController::get_user(const std::string &username) {
  return userlist_m[username];
}

// loads account using cereal
bool UserController::LoadUserList() {
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
        userlist_m.insert(std::make_pair(user.get_username(), user));
      }
      return 1;
    }
  }
  return 0;
}

// saves account using cereal serialization library
// will create new file or overwrite existing file
bool UserController::SaveUserList() {

  // TODO - filename should be a constant throughout the program
  bool savestatus;
  std::string filename = "../data/users/users.xml";
  std::cout << "NUMBER BEING SAVED" << userlist_m.size() << std::endl;
  std::vector<User> uservector;
  // prepare vector of objects to serialize
  for (auto user : userlist_m) {
    uservector.push_back(user.second);
  }
  bool filefound = amphora_util_m.FindFile(filename);
  if (!filefound) {
    // create file if not found/doesn't exist
    std::fstream fs;
    fs.open(filename.data(), std::ios::out);
    fs.close();
    filefound = amphora_util_m.FindFile(filename);
  }
  if (filefound) {
    std::cout << "File found" << std::endl; // debug
    savestatus = amphora_util_m.SaveToFile<User>(filename, uservector);
    if (savestatus) { // if save success + check file -> return true
      return 1;
    }
  }
  return 0;
}

// void UserController::DeleteAccount(const std::string &accountname)
// {
//   accountdata_m.erase(accountname);
// }

// // TODO remove from backend
// // the UI should handle this! ui call FindAccount -> return desired Account
// obj GetAccount
// // displays acccount info in nice format
// void UserController::ViewAccount(const std::string &accountname)
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

// void UserController::ViewAccountList(const std::string &format, const
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

} // namespace core
} // namespace amphora
