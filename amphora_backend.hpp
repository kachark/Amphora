// Utilities for managing account objects


#ifndef __ACCOUNT_UTIL_HPP_INCLUDED__
#define __ACCOUNT_UTIL_HPP_INCLUDED__

#include <vector>
#include "account.hpp"
#include "amphora_util.hpp"


class AmphoraBackend {

public:
  AmphoraBackend();
  void InitAccount(Account &newaccount);
  void EditAccount(Account &account);
  void ViewAccount(Account &account);
  void LoadAccountList();
  void SaveAccountList(Account &newaccount);
  void ViewAccountList(std::string &format, std::string &sortstyle);

private:
  AmphoraUtilities amphora_util_m;
  std::vector<Account> accountlist_m;

};


#endif // ACCOUNT_UTIL_HPP

