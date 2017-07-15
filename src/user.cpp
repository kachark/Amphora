
#include "../include/user.hpp"
#include <cereal/archives/xml.hpp> // serialize in xml format
#include <cereal/types/string.hpp>

void User::clear() {
  username_m.clear();
  password_m.clear();
  datemodified_m.clear();
  datemodified_m.clear();
  accountfileid_m.clear();
}

void User::set_username(const std::string &username) { username_m = username; }

void User::set_password(const std::string &password) { password_m = password; }

void User::set_datecreated(const std::string &date) { datecreated_m = date; }

void User::set_datemodified(const std::string &date) { datemodified_m = date; }

void User::set_accountfileid(const std::string &fileid) {
  accountfileid_m = fileid;
}

std::string User::get_username() const { return username_m; }

std::string User::get_password() const { return password_m; }

std::string User::get_datecreated() const { return datecreated_m; }

std::string User::get_datemodified() const { return datemodified_m; }

template <typename Archive> inline void User::serialize(Archive &ar) {
  ar(username_m, password_m, datecreated_m, datemodified_m);
}

// have to initialize template for loading and saving although there is only a
// single serialization function
template void
User::serialize<cereal::XMLOutputArchive>(cereal::XMLOutputArchive &);
template void
User::serialize<cereal::XMLInputArchive>(cereal::XMLInputArchive &);
