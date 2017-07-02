

#include "amphora_util.hpp"
#include "account.hpp"
#include "user.hpp"
#include <cereal/archives/xml.hpp> // serialize in xml format
#include <cereal/types/string.hpp>
#include <iostream>
#include <fstream>
#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
// #include <boost/filesystem.hpp>

using namespace boost::posix_time;


// retrieves system date and time in nice format
std::string AmphoraUtilities::CurrentDate()
{
  time_facet *facet = new time_facet("%d-%b-%Y %H:%M:%S");
  std::cout.imbue(std::locale(std::cout.getloc(), facet));
  //  cout << second_clock::local_time() << endl;
  std::string date = to_simple_string(second_clock::local_time());
  std::cout << "INSIDE get_date() -> " << date << std::endl;
  return date;
}

// checks if a file is in the pwd
int AmphoraUtilities::CheckFile(const std::string &filename)
{
  //see boost filesystem
  return 0;
}

// outputs vector of strings in nice format
void AmphoraUtilities::PrettyTable(const std::vector<std::string> &data)
{

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

// loads account using cereal
template<typename T> inline
void AmphoraUtilities::LoadFromFile(const std::string &filename, std::vector<T> &buffer)
{
  // might be better to have filename as an arg?
  // std::string filename = "vault.xml";
  // check if filename is in the pwd
  // std::vector<T> loadeddata;
  std::size_t num_saved;
  {
    // open stream
    // HOW TO CHECK IF FILENAME EXISTS OR NOT?
    // IF NOT: create a new vault.xml (default vault filename)
    // IF exists, but file is empty: terminate load process??
    std::ifstream is(filename);
    cereal::XMLInputArchive archive(is);
    // call archive and get number of saved accounts from archive's first index.
    archive( num_saved );
    // loop and call archive for the number of saved accounts, to ensure every account is retrieved.
    for ( auto i = 0; i < num_saved; ++i ) {
      T temp;
      archive( temp );
      buffer.push_back(temp);
      // loadeddata.insert(std::make_pair(temp.get_name(), temp));
    }
      std::cout << "DEBUG: num_saved = " << num_saved << std::endl;
  }

}


// saves account using cereal serialization library
template<typename T> inline
void AmphoraUtilities::SaveToFile(const std::string &filename, std::vector<T> &datalist)
{

  // std::string savedaccount = "vault.xml";
  std::size_t num_saved;
  // std::cout << "NUMBER BEING SAVED" << accountlist_m.size() << std::endl;
  std::cout << "NUMBER BEING SAVED" << datalist.size() << std::endl;
  {
    std::ofstream file( filename );
    cereal::XMLOutputArchive archive( file );

    num_saved = datalist.size();
    archive(num_saved);

    for (auto dataelement : datalist) {
      archive(dataelement);
    }
 } // when archive goes out of scope it is guaranteed to have flushed its
    // contents to its stream
}


// implemented templates above
// explicitely instantiated the templates below to work with User and Account types
template void AmphoraUtilities::LoadFromFile<Account>(const std::string &filename, std::vector<Account> &buffer);
template void AmphoraUtilities::LoadFromFile<User>(const std::string &filename, std::vector<User> &buffer);
template void AmphoraUtilities::SaveToFile<Account>(const std::string &filename, std::vector<Account> &datalist);
template void AmphoraUtilities::SaveToFile<User>(const std::string &filename, std::vector<User> &datalist);





