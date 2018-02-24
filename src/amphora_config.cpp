
#include "amphora_config.hpp"
#include "cereal/archives/xml.hpp" // serialize in xml format
#include "cereal/types/string.hpp"

AmphoraConfig::~AmphoraConfig() {
}

std::string AmphoraConfig::get_user_dir() {
  return user_dir_m;
}

std::string AmphoraConfig::get_account_dir() {
  return account_dir_m;
}

std::string AmphoraConfig::get_crypto_dir() {
  return crypto_dir_m;
}

std::string AmphoraConfig::get_logger_dir() {
  return logger_dir_m;
}

void AmphoraConfig::set_user_dir(const std::string &directory) {
  user_dir_m = directory;
}

void AmphoraConfig::set_account_dir(const std::string &directory) {
  account_dir_m = directory;
}

void AmphoraConfig::set_crypto_dir(const std::string &directory) {
  crypto_dir_m = directory;
}

void AmphoraConfig::set_logger_dir(const std::string &directory) {
  logger_dir_m = directory;
}

template<typename Archive>
inline void AmphoraConfig::serialize(Archive &ar) {
  ar(user_dir_m, account_dir_m, crypto_dir_m, logger_dir_m);
}
