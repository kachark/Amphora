
#ifndef USER_HPP
#define USER_HPP

#include <string>

class User {

 public:
  // default constructor preferred for serialization
  User() = default;

  ~User() = default;

  void clear();

  void set_username(const std::string &username);

  void set_password(const std::string &password);

  void set_datecreated(const std::string &date);

  void set_datemodified(const std::string &date);

  void set_account_file(const std::string &fileid);

  void set_crypto_id(const std::string &cryptofileid);

  void set_salt(const std::string &salt);

  std::string get_username() const;

  std::string get_password() const;

  std::string get_datecreated() const;

  std::string get_datemodified() const;

  std::string get_account_file() const;

  std::string get_crypto_id() const;

  std::string get_salt() const;

  // this method lets cereal know which data members to serialize for this type
  template<typename Archive>
  void serialize(Archive &ar);

 private:
  std::string username_m, password_m, datecreated_m, datemodified_m,
      accountfileid_m, cryptofileid_m, salt_m;
};

#endif // USER_HPP
