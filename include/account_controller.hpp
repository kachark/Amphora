
#ifndef ACCOUNT_CONTROLLER_HPP
#define ACCOUNT_CONTROLLER_HPP

#include "account.hpp"
#include "amphora_util.hpp"
#include "crypto.hpp"
#include "crypto_util.hpp"
#include "user.hpp"
#include <map>

namespace amphora {
namespace core {

class AccountController {

public:
  AccountController();

  void AddAccount(const std::string &name, const std::string &purpose,
                  const std::string &username, const std::string &password,
                  internal::Crypto &crypto, internal::User &currentuser);
  internal::Account EditAccount(const std::string &account); // changed
  void DeleteAccount(const std::string &accountname);
  bool FindAccount(const std::string &accountname); // find AND RETURN
  internal::Account &GetAccount(const std::string &accountname); // new
  void ViewAccount(const std::string &account, internal::Crypto &crypto,
                   internal::User &currentuser);
  bool LoadAccountList(const std::string &fileid);
  bool SaveAccountList(const std::string &fileid);
  void ViewAccountList(const std::string &format, const std::string &sortstyle);

private:
  internal::AmphoraUtilities amphora_util_m;
  internal::CryptoUtilities crypto_util_m; // debug
  internal::Account tempaccount_m;
  std::map<std::string, internal::Account> accountlist_m;
};

} // namespace core
} // namespace amphora

#endif // ACCOUNT_CONTROLLER_HPP
