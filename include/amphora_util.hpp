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
  bool LoadVector(const std::string &filename, std::vector<T> &buffer);

  template<typename T>
  bool SaveVector(const std::string &filename, std::vector<T> &datalist);

  template<typename T>
  bool LoadSingle(const std::string &filename, T &element);

  template<typename T>
  bool SaveSingle(const std::string &filename, T &element);

};

#endif // AMPHORA_UTIL_HPP
