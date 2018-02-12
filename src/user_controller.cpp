

#include "user_controller.hpp"
#include "crypto.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

UserController::UserController(const AmphoraMediator &mediator)
    : mediator_m(mediator) {}

// TODO P1-1 api clarity
void UserController::AddUser(const User &newuser) {

  // store temporary new user in map
  userlist_m.insert(std::make_pair(newuser.get_username(), newuser));
  // clear temporary user
  tempuser_m.clear();
}

// // returns reference to User
User &UserController::get_user(const std::string &username) {
  // TODO if username not in userlist, will crash
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

/* Returns 1 if User within userlist, else return 0 */
bool UserController::CheckUserList(const std::string &username) {
  return userlist_m.count(username);
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
