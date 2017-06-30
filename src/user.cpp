
#include "user.hpp"

void User::set_username(const std::string &username)
{
  User::username_m = username;
}

void User::set_password(const std::string &password)
{
  User::password_m = password;
}

void User::set_datecreated(const std::string &date)
{
  User::datecreated_m = date;
}

void User::set_datemodified(const std::string &date)
{
  User::datemodified_m = date;
}

std::string User::get_username() const
{
  return User::username_m;
}

std::string User::get_password() const
{
  return User::password_m;
}

std::string User::get_datecreated() const
{
  return User::datecreated_m;
}

std::string User::get_datemodified() const
{
  return User::datemodified_m;
}

template<typename Archive> inline
void User::serialize(Archive &ar)
{
  ar( User::username_m, User::password_m, User::datecreated_m, User::datemodified_m );
}

// have to initialize template for loading and saving although there is only a single serialization function
template void User::serialize<cereal::XMLOutputArchive>( cereal::XMLOutputArchive & );
template void User::serialize<cereal::XMLInputArchive>( cereal::XMLInputArchive & );

