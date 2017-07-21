
#ifndef ACCOUNT_MANAGER_HPP
#define ACCOUNT_MANAGER_HPP

#include "account.hpp"
#include "amphora_util.hpp"
#include "crypto_util.hpp"
#include <map>

namespace AmphoraBackend {

class AccountManager {

public:
  AccountManager();

  void AddAccount(const std::string &name, const std::string &purpose,
                  const std::string &username, const std::string &password);
  Account EditAccount(const std::string &account); // changed
  void DeleteAccount(const std::string &accountname);
  bool FindAccount(const std::string &accountname); // find AND RETURN
  Account &GetAccount(const std::string &accountname); // new
  void ViewAccount(const std::string &account);
  bool LoadAccountList(const std::string &fileid);
  bool SaveAccountList(const std::string &fileid);
  void ViewAccountList(const std::string &format, const std::string &sortstyle);

private:
  AmphoraUtilities amphora_util_m;
  CryptoUtilities crypto_util_m; // debug
  Account tempaccount_m;
  std::map<std::string, Account> accountlist_m;
};
}

#endif // ACCOUNT_MANAGER_HPP
