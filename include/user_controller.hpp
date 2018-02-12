
#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include "amphora_mediator.hpp"
#include "amphora_util.hpp"
#include "crypto_controller.hpp"
#include "crypto_util.hpp"
#include "user.hpp"
#include <map>

class UserController {

public:
  // TODO p1-1 copy constructor and destructor
  UserController(const AmphoraMediator &m);
  UserController(const UserController &u);
  ~UserController();

  void AddUser(const User &newuser);
  void DeleteUser(const std::string &username);
  User &get_user(const std::string &username);
  bool CheckUserList(const std::string &username);
  bool LoadUserList();
  bool SaveUserList();
  //     Account EditAccount(const std::string &account); // changed
  //     void ViewAccount(const std::string &account);
  //     void ViewAccountList(const std::string &format, const std::string
  //     &sortstyle);

private:
  AmphoraMediator mediator_m;
  std::map<std::string, User> userlist_m;
};

#endif // USER_CONTROLLER_HPP
