
#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include "amphora_util.hpp"
#include "crypto_manager.hpp"
#include "crypto_util.hpp"
#include "user.hpp"
#include <map>

namespace AmphoraBackend {

class UserManager {

public:
  UserManager();
  // void AddUser(const std::string &username, const std::string &password,
  //              const std::string &salt, const std::string &accountfileid,
  //              const std::string &cryptofileid);
  void AddUser(const std::string &username, const std::string &password,
               CryptoManager &crypto_manager);
  bool VerifyUser(const std::string &username, const std::string &password,
                  CryptoManager &crypto_manager);
  void DeleteUser(const std::string &username);
  bool FindUser(const std::string &accountname); // find AND RETURN
  User &GetUser(const std::string &username);
  bool LoadUserList();
  bool SaveUserList();
  //     Account EditAccount(const std::string &account); // changed
  //     void ViewAccount(const std::string &account);
  //     void ViewAccountList(const std::string &format, const std::string
  //     &sortstyle);

private:
  AmphoraUtilities amphora_util_m;
  CryptoUtilities crypto_util_m;
  User tempuser_m;
  std::map<std::string, User> userlist_m;
};
}

#endif // USER_MANAGER_HPP
