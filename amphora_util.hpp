// Amphora utility functions


#ifndef AMPHORA_UTIL_HPP
#define AMPHORA_UTIL_HPP

#include <string>
#include <vector>

class AmphoraUtilities {

public:
  std::string CurrentDate();
  std::string Encrypt();
  int CheckFile(std::string &filename);
  void PrettyTable(std::vector<std::string> &data);

};

#endif // AMPHORA_UTIL_HPP
