
#ifndef AMPHORA_AMPHORA_CONFIG_HPP
#define AMPHORA_AMPHORA_CONFIG_HPP

#include <string>

class AmphoraConfig {

 public:
//  AmphoraConfig() = default;

//  ~AmphoraConfig();

  std::string get_config_dir();

  std::string get_user_dir();

  std::string get_account_dir();

  std::string get_crypto_dir();

  std::string get_logger_dir();

  void set_config_dir(const std::string &directory);

  void set_user_dir(const std::string &directory);

  void set_account_dir(const std::string &directory);

  void set_crypto_dir(const std::string &directory);

  void set_logger_dir(const std::string &directory);

  template<typename Archive>
  void serialize(Archive &ar);

 private:

  std::string config_dir_m;
  std::string user_dir_m;
  std::string account_dir_m;
  std::string crypto_dir_m;
  std::string logger_dir_m;
};

#endif //AMPHORA_AMPHORA_CONFIG_HPP
