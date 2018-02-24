
#include "amphora_mediator.hpp"
//#include "amphora_util.hpp"
//#include "amphora_config.hpp"
//#include "account_controller.hpp"
//#include "crypto_controller.hpp"
//#include "crypto_util.hpp"
//#include "user_controller.hpp"

AmphoraMediator &AmphoraMediator::operator=(const AmphoraMediator &rhs) {
  if (this != &rhs) {
    // delete old
    // delete[] account_controller_m;
    // delete[] crypto_controller_m;
    // delete[] user_controller_m;
    // copy from rhs
    // account_controller_m = rhs.account_controller_m;
    // crypto_controller_m = rhs.crypto_controller_m;
    // user_controller_m = rhs.crypto_controller_m;
  }
  return *this; // return reference to left-hand side
}

void AmphoraMediator::Setup() {


  // shared pointer Amphora Utilities
  amphora_util_m = std::make_shared<AmphoraUtilities>();

  account_controller_m = AccountController();
  crypto_controller_m = CryptoController();
  user_controller_m = UserController();
  amphora_config_m = AmphoraConfig();
//
//    crypto_util_m = std::unique_ptr<CryptoUtilities>(new CryptoUtilities());
//    account_controller_m =
//            std::unique_ptr<AccountController>(new AccountController(this));
//    crypto_controller_m =
//            std::unique_ptr<CryptoController>(new CryptoController(this));
//    user_controller_m =
//            std::unique_ptr<UserController>(new UserController(this));
//    amphora_config_m = std::unique_ptr<AmphoraConfig>(new AmphoraConfig(this));

  std::string userDir = "../data/users/users.xml";
  amphora_config_m.set_user_dir(userDir);
}

/* Returns current date as string */
std::string AmphoraMediator::get_date() {
  return amphora_util_m->CurrentDate();
}

void AmphoraMediator::UpdateCurrentUser(const std::string &username) {
  current_user_m = user_controller_m.get_user(username);
  current_crypto_m =
      crypto_controller_m.get_crypto(current_user_m.get_crypto_id());
}

/* Add new User */
void AmphoraMediator::NewUser(const std::string &username,
                              const std::string &password) {

  User tempuser;
  std::string date = get_date();
  unsigned int iterations = current_crypto_m.get_hmac_iterations();
  CryptoPP::SecByteBlock accountfileid = crypto_util_m.AES_PRNG(3);
  CryptoPP::SecByteBlock salt =
      crypto_util_m.AES_PRNG(current_crypto_m.get_saltsize());
  std::size_t keysize = current_crypto_m.get_keysize();
  CryptoPP::SecByteBlock hashedpassword =
      crypto_util_m.PBKDF2(iterations, salt, keysize, password);

  tempuser.set_username(username);
  tempuser.set_password(crypto_util_m.SecByteBlockToString(hashedpassword));
  tempuser.set_datecreated(date);
  tempuser.set_datemodified(date);
  tempuser.set_account_file(crypto_util_m.SecByteBlockToString(accountfileid));
  tempuser.set_crypto_id("default");
  tempuser.set_salt(crypto_util_m.SecByteBlockToString(salt));
  user_controller_m.AddUser(tempuser);
  Save(AmphoraType::User);

  tempuser.clear();
}

// TODO p1-6 secure container
bool AmphoraMediator::VerifyUser(const std::string &username,
                                 const std::string &password) {
  // TODO p1-4 error type
  bool userfound = CheckUser(username);
  if (!userfound) {
    // TODO p1-1
    return 0; // User not found in database
    // move this line to cli.cpp
    // std::cout << "User not found in userdata" << std::endl;
  } else { // username in database, now verify the password
    // compare this user's pw/key with what was passed into this function
    // User loggedin = userlist_m[username];
    User tmp_user = user_controller_m.get_user(username);
    bool crypto_verified = VerifyCrypto(tmp_user, password);
    if (crypto_verified) {
      return 1;
    }
  }
  return 0; // default return, user not found or bad password
}

/* Verifies a Users cryptographic credentials */
// TODO p1-1 functionality doesn't make sense
bool AmphoraMediator::VerifyCrypto(const User &user,
                                   const std::string &password) {
  // TODO p1-3 Move to it's own function, return bool
  Crypto tmp_crypto = crypto_controller_m.get_crypto(user.get_crypto_id());
  // TODO p1-6 don't st ore secure data in std::strings
  // access this user's crypto settings
  const CryptoPP::SecByteBlock salt = tmp_crypto.get_salt();
  std::size_t keysize = tmp_crypto.get_keysize();
  unsigned int iterations = tmp_crypto.get_hmac_iterations();
  CryptoPP::SecByteBlock masterkey =
      crypto_util_m.PBKDF2(iterations, salt, keysize, password);

  // TODO p1-6 use cryptopp VerifyBufsEqual or similar
  // if (masterkey == loggedin.get_password()) {
  // if (masterkey.compare(loggedin.get_password())) {
  if (std::lexicographical_compare(masterkey.begin(), masterkey.end(),
                                   user.get_password().begin(),
                                   user.get_password().end())) {
    return 1;
  }
  return 0;
}

/* Checks if User exists
0: Does not exist
1: Exists */
bool AmphoraMediator::CheckUser(const std::string &username) {
  if (user_controller_m.CheckUserList(username)) {
    return true; // found
  } else {       // account key not found
    return false;
  }
}

void AmphoraMediator::NewAccount(const std::string &name,
                                 const std::string &purpose,
                                 const std::string &username,
                                 const std::string &password) {

  Account tempaccount;
  std::string date = get_date();

  // Encrypt username
  std::string key = current_user_m.get_password();
  CryptoPP::SecByteBlock cryptokey = crypto_util_m.StringToSecByteBlock(key);
  CryptoPP::SecByteBlock iv =
      crypto_util_m.AES_PRNG(current_crypto_m.get_ivsize());
  std::string strIV = crypto_util_m.SecByteBlockToString(iv);
  std::string encrypted_uname =
      crypto_util_m.AES_GCM_Encrypt(username, cryptokey, iv);
  encrypted_uname = strIV + encrypted_uname;

  // Encrypt password
  CryptoPP::SecByteBlock iv2 =
      crypto_util_m.AES_PRNG(current_crypto_m.get_ivsize());
  std::string strIV2 = crypto_util_m.SecByteBlockToString(iv2);
  std::string encrypted_pw =
      crypto_util_m.AES_GCM_Encrypt(password, cryptokey, iv2);
  encrypted_pw = strIV2 + encrypted_pw;

  tempaccount.set_name(name);
  tempaccount.set_details(purpose);
  tempaccount.set_username(encrypted_uname);
  tempaccount.set_password(encrypted_pw);
  tempaccount.set_datecreated(date);
  tempaccount.set_datemodified(date);

  account_controller_m.AddAccount(tempaccount);
  Save(AmphoraType::Account);
  tempaccount.clear();
}

Account AmphoraMediator::GetAccount(const std::string &accountname) {
  return account_controller_m.GetAccount(accountname);
}
//
///* Encryption/Decryption operation different for Accounts and Users */
//template<typename T>
//void AmphoraMediator::Encrypt(T, AmphoraType) {
//    crypto_util_m.AES_GCM_Encrypt(....)
//}
//
//template<typename T>
//void AmphoraMediator::Decrypt(T, AmphoraType) {
//    crypto_util_m.AES_GCM_Decrypt(...)
//}

/* returns bool/error type
 * pass in buffer to get filled with contents of filename
 * cli load(abc.xml, account id) --> mediator case: account| load accountcontroller)*/
// TODO filename should be read from a config file

// instead make template and genericize this
bool AmphoraMediator::Load(AmphoraType id) {

  std::string user_directory = amphora_config_m.get_user_dir();
  std::string accountDir = amphora_config_m.get_account_dir();
  std::string accountFileID = current_user_m.get_account_file();
  // TODO
  std::string accountPath = accountDir + accountFileID + ".xml";
  std::string crypto_directory = amphora_config_m.get_crypto_dir();

  std::string account_id = current_user_m.get_account_file();

  // weak pointer to utilities
  std::weak_ptr<AmphoraUtilities> wP_util(amphora_util_m);

  switch (id) {
    case AmphoraType::User: {
      return user_controller_m.LoadUserList(wP_util, user_directory);
    }

    case AmphoraType::Account: {
      return account_controller_m.LoadAccountList(wP_util, accountPath);
    }

    case AmphoraType::Crypto: {
      return crypto_controller_m.LoadCrypto(wP_util, crypto_directory);
    }

    case AmphoraType::Config: {
      return false;
//          return config_m;
    }
  }

//    return amphora_util_m->LoadFromFile(filename, buffer);
}

bool AmphoraMediator::Save(AmphoraType id) {

  std::string userDir = amphora_config_m.get_user_dir();
  std::string accountDir = amphora_config_m.get_account_dir();
  std::string accountFileID = current_user_m.get_account_file();
  // TODO
  std::string accountPath = accountDir + accountFileID + ".xml";
  std::string cryptoDir = amphora_config_m.get_crypto_dir();

  // weak pointer to utilities
  std::weak_ptr<AmphoraUtilities> wP_util(amphora_util_m);

  switch (id) {
    case AmphoraType::User: {
      return user_controller_m.SaveUserList(wP_util, userDir);
    }

    case AmphoraType::Account: { // TODO need to send fileid
      return account_controller_m.SaveAccountList(wP_util, accountPath);
    }

    case AmphoraType::Crypto: {
      return crypto_controller_m.SaveCrypto(wP_util, cryptoDir);
    }

    case AmphoraType::Config: {
      return false;
    }
  }
//return amphora_util_m->SaveToFile(filename, buffer);
}

//void AmphoraMediator::ElementChanged(const Element &element) {
//
//}



// destructors
//AccountController::~AccountController() {}
//CryptoController::~CryptoController() {}
//UserController::~UserController() {}
//AmphoraConfig::~AmphoraConfig() {}
