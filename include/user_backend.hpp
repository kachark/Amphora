
#ifndef USER_BACKEND_HPP
#define USER_BACKEND_HPP

#include <string>
#include <map>

namespace AmphoraBackend
{

  class ManageUser {

  public:
    AmphoraBackend();
    bool CheckUser(const std::string &username, const std::string &password);
    // TODO add after refactoring backend
    // void AddUser(const std::string &username, const std::string &password);
    // void EditUser(const std::string &username);


    void AddAccount(const std::string &name, const std::string &purpose, const std::string &username, const std::string &password);
    Account EditAccount(const std::string &account); // changed
    void DeleteAccount(const std::string &accountname);
    bool FindAccount(const std::string &accountname);
    Account GetAccount(const std::string &accountname); // new
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

}

#endif // USER_BACKEND_HPP


