
#ifndef AMPHORA_MEDIATOR_HPP
#define AMPHORA_MEDIATOR_HPP

#include "account.hpp"
#include "crypto.hpp"
#include "user.hpp"
#include <memory>
#include <string>

/* Forward Declarations */
class AccountController;

class UserController;

class CryptoController;

class CryptoUtilities;

class AmphoraUtilities;

class AmphoraMediator {

public:
    // TODO p1-1 overload = operator, copy constructor and destructor
    AmphoraMediator() = default;

    AmphoraMediator(const AmphoraMediator &m); // copy constructor
    ~AmphoraMediator();

    AmphoraMediator &operator=(const AmphoraMediator &m);

    void Setup();

    std::string get_date();

    /* Users */
    void NewUser(const std::string &username, const std::string &password); // ?
    void DeleteUser(const std::string &username, const std::string &password);

    bool VerifyUser(const std::string &username, const std::string &password);

    bool CheckUser(const std::string &username);

    void UpdateCurrentUser(const std::string &username);

    void NewAccount(const std::string &name, const std::string &purpose,
                    const std::string &username, const std::string &password);

    Account GetAccount(const std::string &accountname);

    bool LoadUsers();

    bool LoadCrypto();

    bool LoadAccountList();

    void ShowSession();

    void SaveSession();

    void ShowAccount();

    /* Utils */
    bool FindFile(const std::string &filename);

    template<typename T>
    bool Load(const std::string &filename, std::vector<T> &buffer);

    template<typename T>
    bool Save(const std::string &filename, std::vector<T> &datalist);

private:
    // TODO p1-4
    void Encrypt();
    void Decrypt();

    bool VerifyCrypto(const User &user, const std::string &password);

    // each of the controllers should be able to reference the mediator to
    // access the util objects
    std::unique_ptr<AccountController> account_controller_m;
    std::unique_ptr<CryptoController> crypto_controller_m;
    std::unique_ptr<UserController> user_controller_m;
    std::unique_ptr<CryptoUtilities> crypto_util_m;
    std::unique_ptr<AmphoraUtilities> amphora_util_m;
    // std::unique_ptr<Logger> logger_m;

    User current_user_m;
    Crypto current_crypto_m;
    // Error error_m;
};

#endif // AMPHORA_MEDIATOR_HPP
