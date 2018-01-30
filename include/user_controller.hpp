
#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include "amphora_util.hpp"
#include "crypto_controller.hpp"
#include "crypto_util.hpp"
#include "user.hpp"
#include <map>

namespace amphora {
namespace core {

class UserController {

public:
  UserController();
  // void AddUser(const std::string &username, const std::string &password,
  //              const std::string &salt, const std::string &accountfileid,
  //              const std::string &cryptofileid);
  void AddUser(const std::string &username, const std::string &password,
               CryptoController &crypto_controller);
  bool VerifyUser(const std::string &username, const std::string &password,
                  CryptoController &crypto_controller);
  void DeleteUser(const std::string &username);
  bool FindUser(const std::string &accountname); // find AND RETURN
  internal::User &get_user(const std::string &username);
  bool LoadUserList();
  bool SaveUserList();
  //     Account EditAccount(const std::string &account); // changed
  //     void ViewAccount(const std::string &account);
  //     void ViewAccountList(const std::string &format, const std::string
  //     &sortstyle);

private:
  internal::AmphoraUtilities amphora_util_m;
  internal::CryptoUtilities crypto_util_m;
  internal::User tempuser_m;
  std::map<std::string, internal::User> userlist_m;
};

} // namespace core
} // namespace amphora

#endif // USER_CONTROLLER_HPP
