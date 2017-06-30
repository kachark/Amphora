
#ifndef USER_HPP
#define USER_HPP

#include <cereal/archives/xml.hpp> // serialize in xml format
#include <cereal/types/string.hpp>

class User {

public:
  // default constructor preferred for serialization
  User() = default;

  void set_username(const std::string &username);
  void set_password(const std::string &password);
  void set_datecreated(const std::string &date);
  void set_datemodified(const std::string &date);
  std::string get_username() const;
  std::string get_password() const;
  std::string get_datecreated() const;
  std::string get_datemodified() const;


  // this method lets cereal know which data members to serialize for this type
  template <typename Archive>
  void serialize(Archive & ar);

private:
  std::string username_m, password_m, datecreated_m, datemodified_m;

};

#endif // USER_HPP
