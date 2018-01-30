

#include "account.hpp"
#include "cereal/archives/xml.hpp" // serialize in xml format
#include "cereal/types/string.hpp"

namespace amphora {
namespace internal {

void Account::clear() {
  Account::name_m.clear();
  Account::purpose_m.clear();
  Account::username_m.clear();
  Account::password_m.clear();
  Account::datemodified_m.clear();
  Account::datemodified_m.clear();
}

void Account::set_name(const std::string &name) { Account::name_m = name; }

void Account::set_purpose(const std::string &purpose) {
  Account::purpose_m = purpose;
}

void Account::set_username(const std::string &username) {
  Account::username_m = username;
}

void Account::set_password(const std::string &password) {
  Account::password_m = password;
}

void Account::set_datecreated(const std::string &date) {
  Account::datecreated_m = date;
}

void Account::set_datemodified(const std::string &date) {
  Account::datemodified_m = date;
}

std::string Account::get_name() const { return Account::name_m; }

std::string Account::get_purpose() const { return Account::purpose_m; }

std::string Account::get_username() const { return Account::username_m; }

std::string Account::get_password() const { return Account::password_m; }

std::string Account::get_datecreated() const { return Account::datecreated_m; }

std::string Account::get_datemodified() const {
  return Account::datemodified_m;
}

template <typename Archive> inline void Account::serialize(Archive &ar) {
  ar(Account::name_m, Account::purpose_m, Account::username_m,
     Account::password_m, Account::datecreated_m, Account::datemodified_m);
}

// have to initialize template for loading and saving although there is only a
// single serialization function
template void
Account::serialize<cereal::XMLOutputArchive>(cereal::XMLOutputArchive &);
template void
Account::serialize<cereal::XMLInputArchive>(cereal::XMLInputArchive &);

} // namespace internal
} // namespace amphora
