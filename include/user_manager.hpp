
#ifndef USER_MANAGER_HPP
#define USER_MANAGER_HPP

#include "user.hpp"
#include "amphora_util.hpp"
#include "crypto_util.hpp"
#include <map>


namespace AmphoraBackend
{

  class UserManager {

  public:
    UserManager();
    bool CheckUser(const std::string &username, const std::string &password);

    void AddUser(const std::string &username, const std::string &password);
//     Account EditAccount(const std::string &account); // changed
    void DeleteUser(const std::string &username);
    bool FindAccount(const std::string &accountname); // find AND RETURN
//     // Account GetAccount(const std::string &accountname); // new
//     void ViewAccount(const std::string &account);
    bool LoadUserList();
    bool SaveUserList();
//     void ViewAccountList(const std::string &format, const std::string &sortstyle);

  private:
    AmphoraUtilities amphora_util_m;
    CryptoUtilities crypto_util_m;
    User tempuser;
    std::map<std::string, User> userdata_m;

    void EncryptUsers(); // encrypts Users inside userdata_m
    void DecryptUsers(); // decrypts Users

  };

}


#endif // USER_MANAGER_HPP

