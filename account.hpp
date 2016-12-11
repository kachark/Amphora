
#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP


// needs cereal headers here so it knows about Archive class etc.
// this gets passed to account_util_new.cpp through account_util_new.hpp

//#include "aes.h"
#include <cereal/archives/xml.hpp> // serialize in xml format
#include <cereal/types/string.hpp>



class Account {

public:
  // default constructor preferred for serialization
  Account() = default;
  //Account() = {};

  void set_name(std::string &name);
  void set_purpose(std::string &purpose);
  void set_username(std::string &username);
  void set_password(std::string &password);
  void set_datecreated(std::string &date);
  void set_datemodified(std::string &date);
  void set_account_info(Account &account);
  std::string get_name();
  std::string get_purpose();
  std::string get_username();
  std::string get_password();
  std::string get_datecreated();
  std::string get_datemodified();


  // this method lets cereal know which data members to serialize for this type
  template <typename Archive>
  void serialize(Archive & ar)
  {
    // serialize things by passing the to the archive
    ar( Account::name_m, Account::purpose_m, Account::username_m, Account::password_m, Account::datecreated_m, Account::datemodified_m );
  }

private:
  std::string name_m, purpose_m, username_m, password_m, datecreated_m, datemodified_m;

};

#endif // ACCOUNT_HPP







