// Amphora utility functions

#ifndef AMPHORA_UTIL_HPP
#define AMPHORA_UTIL_HPP

#include <string>
#include <vector>

namespace amphora {
namespace internal {

class AmphoraUtilities {

public:
  std::string CurrentDate();
  bool FindFile(const std::string &filename);
  void PrettyTable(const std::vector<std::string> &data);

  template <typename T>
  bool LoadFromFile(const std::string &filename, std::vector<T> &buffer);

  template <typename T>
  bool SaveToFile(const std::string &filename, std::vector<T> &datalist);

private:
};

} // namespace internal
} // namespace amphora

#endif // AMPHORA_UTIL_HPP
