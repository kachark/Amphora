
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <string>

class Account {

 public:
  Account() = default;

  ~Account() = default;

  void clear();

  void set_name(const std::string &name);

  void set_details(const std::string &purpose);

  void set_username(const std::string &username);

  void set_password(const std::string &password);

  void set_datecreated(const std::string &date);

  void set_datemodified(const std::string &date);

  void set_account_info(const Account &account);

  std::string get_name() const;

  std::string get_details() const;

  std::string get_username() const;

  std::string get_password() const;

  std::string get_datecreated() const;

  std::string get_datemodified() const;

  // this method lets cereal know which data members to serialize for this type
  template<typename Archive>
  void serialize(Archive &ar);

 private:
  std::string name_m, details_m, username_m, password_m, datecreated_m,
      datemodified_m;
};

#endif // ACCOUNT_HPP
