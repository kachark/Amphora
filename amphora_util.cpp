

#include "amphora_util.hpp"
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


// encrypts account information
std::string AmphoraUtilities::Encrypt()
{
  std::cout << "inside encrypt";
  return("");
}

int AmphoraUtilities::CheckFile(std::string &filename)
{
  //see boost filesystem
  return 0;
}

// OPTIMIZE THIS FUNCTION
// outputs vector of strings in nice format
void AmphoraUtilities::PrettyTable(std::vector<std::string> &data)
{

  int index = 0;

  // get number of chars of largest string in data
  std::size_t largestaccountname = 0;
  for (auto it = std::begin(data); it != std::end(data); ++it) {
    index += 1;
    std::size_t namesize = it->length();
    if (namesize >= largestaccountname) {
      largestaccountname = namesize;
    }
  }

  // define table format
  int columncount = 4;
  std::size_t columnwidth = largestaccountname + 2;
  // std::char delimiterchar = ' ';

  // format table elements
  int c = 0;
  std::size_t delimitersize = 0;
  for (auto it = std::begin(data); it != std::end(data); ++it) {
    std::string delimiter;
    std::string token = *it;
    if (token.length() != columnwidth) {
      delimitersize = columnwidth - token.length();
      // delimiter.assign(delimitersize, delimiterchar);
      delimiter.assign(delimitersize, ' ');
      token = token + delimiter;
    }
    if (c < columncount) {
      std::cout << token;
      ++c;
    } else {
      std::cout << std::endl;
      // although c is reset here, the for loop is incrementing right after!!
      c = 0;
    }

  }



//   int columncount = 4;
//   int c = 0;
//   for (int i = 0; i != index; ++i, ++c) {
//     if (c != columncount) {
//       std::cout << data[i] << delimiter;
//     }
//     else {
//       std::cout << std::endl;
//       c = 0;
//     }
//   }


// columns size = largest possible accountname + 2 spaces = ?? chars
  // 4 columns in total
  // don't want to size of table to be based off of terminal size since it's dependent on operating system

}
