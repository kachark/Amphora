// Amphora utility functions

#ifndef AMPHORA_UTIL_HPP
#define AMPHORA_UTIL_HPP

#include <string>
#include <vector>

class AmphoraUtilities {

 public:
  AmphoraUtilities() = default;

  ~AmphoraUtilities() = default;

  std::string CurrentDate();

  bool FindFile(const std::string &filename);

  // TODO move to cli.cpp
  void PrettyTable(const std::vector<std::string> &data);

  template<typename T>
  bool LoadFromFile(const std::string &filename, std::vector<T> &buffer);

  template<typename T>
  bool SaveToFile(const std::string &filename, std::vector<T> &datalist);

};

#endif // AMPHORA_UTIL_HPP
