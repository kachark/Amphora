// Utilities for managing account objects


#ifndef __ACCOUNT_UTIL_HPP_INCLUDED__
#define __ACCOUNT_UTIL_HPP_INCLUDED__

#include "account.hpp"
#include "amphora_util.hpp"
#include <map>

//TODO
#include "crypto_util.hpp"

class AmphoraBackend {

public:
  AmphoraBackend();
  void AddAccount(const std::string &name, const std::string &purpose, const std::string &username, const std::string &password);
  void EditAccount(const std::string &account);
  void DeleteAccount(const std::string &accountname);
  bool FindAccount(const std::string &accountname);
  void ViewAccount(const std::string &account);
  void LoadAccountList();
  void SaveAccountList();
  void ViewAccountList(const std::string &format, const std::string &sortstyle);

private:
  AmphoraUtilities amphora_util_m;
  CryptoUtilities crypto_util_m;
  Account tempAccount;
  std::map<std::string, Account> accountdata_m;

  void ClearTempAccount();

};


#endif // ACCOUNT_UTIL_HPP

