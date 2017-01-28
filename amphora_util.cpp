

#include "amphora_util.hpp"
#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
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

std::string AmphoraUtilities::GetSHA256(const std::string &message)
{

  //Crypto++ Wiki:
  //crypto++ follows a 'pipeline' paradigm whereby data flows from a source to a sink
  //along the way to the sink, the data is filtered and transformed before being released at the sink

  CryptoPP::SHA256 hashfcn; // hash function type
  std::string hashedword = "";
  // the message originiates as a StringSource, a Source for character arrays and strings
  // the message passes through HashFilter which takes the desired hash function type and output encoding as input
  // the message ends up at StringSink
  CryptoPP::StringSource s(message, true,
      new CryptoPP::HashFilter(hashfcn,
      new CryptoPP::HexEncoder(new CryptoPP::StringSink(hashedword))));
  return(hashedword);
}

