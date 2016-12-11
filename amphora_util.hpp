// Amphora utility functions


#ifndef AMPHORA_UTIL_HPP
#define AMPHORA_UTIL_HPP

#include <string>

class AmphoraUtilities {

public:
  std::string CurrentDate();
  std::string Encrypt();
  int CheckFile(std::string &filename);

};

#endif // AMPHORA_UTIL_HPP
