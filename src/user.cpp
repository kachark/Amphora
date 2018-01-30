
#include "user.hpp"
#include "cereal/archives/xml.hpp" // serialize in xml format
#include "cereal/types/string.hpp"

namespace amphora {
namespace internal {

void User::clear() {
  username_m.clear();
  password_m.clear();
  salt_m.clear();
  datemodified_m.clear();
  datemodified_m.clear();
  accountfileid_m.clear();
  cryptofileid_m.clear();
}

void User::set_username(const std::string &username) { username_m = username; }

void User::set_password(const std::string &password) { password_m = password; }

void User::set_datecreated(const std::string &date) { datecreated_m = date; }

void User::set_datemodified(const std::string &date) { datemodified_m = date; }

void User::set_accountfileid(const std::string &fileid) {
  accountfileid_m = fileid;
}

void User::set_cryptoname(const std::string &cryptofileid) {
  cryptofileid_m = cryptofileid;
}

void User::set_salt(const std::string &salt) { salt_m = salt; }

std::string User::get_username() const { return username_m; }

std::string User::get_password() const { return password_m; }

std::string User::get_datecreated() const { return datecreated_m; }

std::string User::get_datemodified() const { return datemodified_m; }

std::string User::get_accountfileid() const { return accountfileid_m; }

std::string User::get_cryptoname() const { return cryptofileid_m; }

std::string User::get_salt() const { return salt_m; }

template <typename Archive> inline void User::serialize(Archive &ar) {
  ar(username_m, password_m, salt_m, datecreated_m, datemodified_m,
     accountfileid_m, cryptofileid_m);
}

// have to initialize template for loading and saving although there is only a
// single serialization function
template void
User::serialize<cereal::XMLOutputArchive>(cereal::XMLOutputArchive &);
template void
User::serialize<cereal::XMLInputArchive>(cereal::XMLInputArchive &);

} // namespace internal
} // namespace amphora
