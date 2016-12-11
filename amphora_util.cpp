

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

