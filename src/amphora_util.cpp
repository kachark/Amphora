

#include "amphora_util.hpp"
#include "account.hpp"
#include "amphora_config.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/archives/xml.hpp"
#include "cereal/types/string.hpp"
#include "crypto.hpp"
#include "user.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <locale>

// TODO p2-2
using namespace boost::posix_time;

/* using namespace boost::filesystem; */

// retrieves system date and time in nice format
std::string AmphoraUtilities::CurrentDate() {
  time_facet *facet = new time_facet("%d-%b-%Y %H:%M:%S");
  std::cout.imbue(std::locale(std::cout.getloc(), facet));
  //  cout << second_clock::local_time() << endl;
  std::string date = to_simple_string(second_clock::local_time());
  return date;
}

// checks if a file is in the pwd
bool AmphoraUtilities::FindFile(const std::string &filename) {
  // TODO
  // need to get relative path to some directory holding .xml files
  // need to define where the .xml files should reside by default!!
  return boost::filesystem::exists(filename);
}

// outputs vector of strings in nice format
void AmphoraUtilities::PrettyTable(const std::vector<std::string> &data) {

  // get largest string of characters
  std::size_t largestelement = 0;
  for (auto element : data) {
    std::size_t elementsize = element.length();
    if (elementsize > largestelement) {
      largestelement = elementsize;
    }
  }

  // define table format
  int numcolumns = 4;
  std::size_t columnwidth = largestelement + 2;
  char delimiterchar = ' ';

  // format table elements
  int currentcolumn = 1;
  std::size_t delimitersize = 0;
  for (auto element : data) {
    std::string delimiter;
    std::string token = element;
    std::size_t tokenlength = element.length();
    if (tokenlength != columnwidth) {
      delimitersize = columnwidth - tokenlength;
      delimiter.assign(delimitersize, delimiterchar);
      token = token + delimiter;
    }

    if (currentcolumn != numcolumns) {
      std::cout << token;
      currentcolumn += 1;
    } else if (currentcolumn == numcolumns) {
      std::cout << token << std::endl;
      currentcolumn = 1;
    }
  }
}

// deserializes vector of data using cereal serialization library
template<typename T>
inline bool AmphoraUtilities::LoadVector(const std::string &filename,
                                         std::vector<T> &buffer) {
  std::size_t num_saved;
  try {
    {
      std::ifstream is(filename);
      cereal::XMLInputArchive archive(is);
      // call archive and get number of saved accounts from archive's first
      // index.
      archive(num_saved);
      // loop and call archive for the number of saved accounts, to ensure every
      // account is retrieved.
      for (auto i = 0; i < num_saved; ++i) {
        T temp;
        archive(temp);
        buffer.push_back(temp);
      }
      std::cout << "DEBUG: num_saved = " << num_saved << std::endl;
    }
  } catch (cereal::Exception &e) {
    std::cout << filename << " is EMPTY" << std::endl;
    return false;
  }
  return true;
}

// serializes vector of objects using cereal serialization library
template<typename T>
inline bool AmphoraUtilities::SaveVector(const std::string &filename,
                                         std::vector<T> &datalist) {
  std::size_t num_saved;
  std::cout << "NUMBER BEING SAVED" << datalist.size() << std::endl;
  try {
    {
      std::ofstream file(filename);
      cereal::XMLOutputArchive archive(file);

      num_saved = datalist.size();
      archive(cereal::make_nvp("Total: ", num_saved));

      for (auto dataelement : datalist) {
        archive(dataelement);
      }
    } // when archive goes out of scope it is guaranteed to have flushed its
    // contents to its stream
  } catch (cereal::Exception &e) {
    std::cout << "Failed to save " << filename << std::endl;
    return false;
  }
  return true;
}

template<typename T>
bool AmphoraUtilities::LoadSingle(const std::string &filename, T &element) {
  try {
    {
      std::ifstream is(filename);
      cereal::XMLInputArchive archive(is);
      archive(element);
    }
  } catch (cereal::Exception &e) {
    std::cout << filename << " is EMPTY" << std::endl;
    return false;
  }
  return true;
}

template<typename T>
bool AmphoraUtilities::SaveSingle(const std::string &filename, T &element) {
  try {
    {
      std::ofstream file(filename);
      cereal::XMLOutputArchive archive(file);

//      archive(cereal::make_nvp("Total: ", num_saved));

      archive(element);
    } // when archive goes out of scope it is guaranteed to have flushed its
    // contents to its stream
  } catch (cereal::Exception &e) {
    std::cout << "Failed to save " << filename << std::endl;
    return false;
  }
  return true;
}

// implemented templates above
// explicitely instantiated the templates below to work with User, Account,
// Crypto types
template bool
AmphoraUtilities::LoadVector<Account>(const std::string &filename,
                                      std::vector<Account> &buffer);

template bool AmphoraUtilities::LoadVector<User>(const std::string &filename,
                                                 std::vector<User> &buffer);

template bool
AmphoraUtilities::LoadVector<Crypto>(const std::string &filename,
                                     std::vector<Crypto> &buffer);

template bool
AmphoraUtilities::SaveVector<Account>(const std::string &filename,
                                      std::vector<Account> &datalist);

template bool AmphoraUtilities::SaveVector<User>(const std::string &filename,
                                                 std::vector<User> &datalist);

template bool
AmphoraUtilities::SaveVector<Crypto>(const std::string &filename,
                                     std::vector<Crypto> &datalist);

template bool
AmphoraUtilities::SaveSingle(const std::string &filename, AmphoraConfig &element);

template bool
AmphoraUtilities::LoadSingle(const std::string &filename, AmphoraConfig &element);
