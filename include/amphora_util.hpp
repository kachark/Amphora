// Amphora utility functions


#ifndef AMPHORA_UTIL_HPP
#define AMPHORA_UTIL_HPP

#include <string>
#include <vector>

class AmphoraUtilities {

public:
  std::string CurrentDate();
  std::string Encrypt();
  int CheckFile(const std::string &filename);
  void PrettyTable(const std::vector<std::string> &data);
  std::string GetPBKDF2(const std::string &message);
  std::string GetSalt(const size_t &saltlength);

private:

};

#endif // AMPHORA_UTIL_HPP
