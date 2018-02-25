

#include "user_controller.hpp"
#include "crypto.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

// TODO P1-1 api clarity
void UserController::AddUser(const User &newuser) {

  // store temporary new user in map
  userlist_m.insert(std::make_pair(newuser.get_username(), newuser));
}

// // returns reference to User
User &UserController::get_user(const std::string &username) {
  // TODO if username not in userlist, will crash
  return userlist_m[username];
}

// loads account using cereal
bool UserController::LoadUserList(std::weak_ptr<AmphoraUtilities> wP_util, const std::string &filename) {
  std::shared_ptr<AmphoraUtilities> sP_util = wP_util.lock();

  // TODO - ensure file exists!
  bool loadstatus;
//  std::string filename = "../data/users/users.xml";
  std::vector<User> uservector;
  if (sP_util) {
    if (sP_util->FindFile(filename)) {  // check if file exists in directory
      std::cout << "File found" << std::endl; // debug
      loadstatus = sP_util->LoadVector<User>(filename, uservector);
      if (loadstatus) { // if load success + check file -> return true
        // populate memory
        for (auto user : uservector) {
          userlist_m.insert(std::make_pair(user.get_username(), user));
        }
        return true;
      }
    }
    return false;
  } else {
    return false;
  }
}

/* Returns 1 if User within userlist, else return 0 */
bool UserController::CheckUserList(const std::string &username) {
  return userlist_m.count(username);
}

// saves account using cereal serialization library
// will create new file or overwrite existing file
bool UserController::SaveUserList(std::weak_ptr<AmphoraUtilities> wP_util, const std::string &filename) {
  std::shared_ptr<AmphoraUtilities> sP_util = wP_util.lock();

  // TODO - filename should be a constant throughout the program
  bool savestatus;
//  std::string filename = "../data/users/users.xml";
  std::cout << "NUMBER BEING SAVED" << userlist_m.size() << std::endl;
  std::vector<User> uservector;
  // prepare vector of objects to serialize
  for (auto user : userlist_m) {
    uservector.push_back(user.second);
  }
  bool filefound = sP_util->FindFile(filename);
  if (sP_util) {
    if (!filefound) {
      // create file if not found/doesn't exist
      std::fstream fs;
      fs.open(filename.data(), std::ios::out);
      fs.close();
      bool filefound = sP_util->FindFile(filename);
    }
    if (filefound) {
      std::cout << "File found" << std::endl; // debug
      savestatus = sP_util->SaveVector<User>(filename, uservector);
      if (savestatus) { // if save success + check file -> return true
        return true;
      }
    }
  } else {
    return false;
  }
}
