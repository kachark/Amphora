
#ifndef ACCOUNT_CONTROLLER_HPP
#define ACCOUNT_CONTROLLER_HPP

#include "account.hpp"
#include "amphora_mediator.hpp"
// #include "amphora_util.hpp"
#include "crypto.hpp"
// #include "crypto_util.hpp"
#include "user.hpp"
#include <map>

class AccountController {

public:
    // TODO p1-1 copy constructor and destructor

    AccountController(const AmphoraMediator &m);

    AccountController(const AccountController &a);

    ~AccountController() = default;

    AccountController &operator=(const AccountController &rhs);

    void set_user(const User &user);

    User get_user();

    void AddAccount(const Account &account);

    Account EditAccount(const std::string &account); // changed
    void DeleteAccount(const std::string &accountname);

    bool FindAccount(const std::string &accountname);    // find AND RETURN
    Account &GetAccount(const std::string &accountname); // new
    void ViewAccount(const std::string &account, Crypto &crypto,
                     User &currentuser);

    // TODO p1-1 acoountcontrollers should be tied to a User. set_user()
    bool LoadAccountList(const std::string &fileid);

    bool SaveAccountList(const std::string &fileid);

    void ViewAccountList(const std::string &format, const std::string &sortstyle);

private:
    AmphoraMediator mediator_m;
    User account_owner_m;
    // TODO p1-1 does this make sense??
    Account tempaccount_m;
    std::map<std::string, Account> accountlist_m;
};

#endif // ACCOUNT_CONTROLLER_HPP
