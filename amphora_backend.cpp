
#include "amphora_backend.hpp"
#include <iostream>
#include <fstream>
#include <vector>

AmphoraBackend::AmphoraBackend()
{

}

// sets first-time account member information
void AmphoraBackend::InitAccount(Account &account)
{
  std::string user;
  std::string date;

  std::cout << "INSIDE modify_account\n";

  // populate account object members for the first time
  std::cout << "first time creating account" << std::endl;

  std::cout << "Please enter the name of the account\n";
  getline(std::cin, user);
  account.set_name(user);

  std::cout << "Please enter the purpose of the account\n";
  getline(std::cin, user);
  account.set_purpose(user);

  std::cout << "Please enter the username for this account\n";
  getline(std::cin, user);
  account.set_username(user);

  std::cout << "Please enter the password for this account\n";
  getline(std::cin, user);
  account.set_password(user);

  date = amphora_util_m.CurrentDate();
  account.set_datecreated(date);
  account.set_datemodified(date);
}

// edit account information
// make sure to ask user to enter password twice to make sure they entered correctly
void AmphoraBackend::EditAccount(Account &account)
{
  std::string user;
  // bool editing = true;
  while (1) {
    AmphoraBackend::ViewAccount(account);
    std::cout << "\nWhat would you like to edit?\n(1): Name\t(2): Purpose\t(3): Username\t(4): Password\t(5): Finish edit\n";
    getline(std::cin, user);

    if (user == "1") {
      std::cout << "Enter a name for this account:\t";
      getline(std::cin, user);
      account.set_name(user);
    }
    if (user == "2") {
      std::cout << "Enter the purpose of this account:\t";
      getline(std::cin, user);
      account.set_purpose(user);
    }
    if (user == "3") {
      std::cout << "Enter the username for this account:\t";
      getline(std::cin, user);
      account.set_username(user);
    }
    if (user == "4") {
      std::cout << "Enter the password for this account:\t";
      getline(std::cin, user);
      account.set_password(user);
    }
    if (user == "5") {
      std::cout << "****** Finished Editing... \n";
      //account.date_mod = get_date();
      break;
    }
  }
}


// displays acccount info in nice format
void AmphoraBackend::ViewAccount(Account &account)
{
  std::cout << "Name: \t\t" << account.get_name() << std::endl;
  std::cout << "Purpose: \t" << account.get_purpose() << std::endl;
  std::cout << "Username: \t" << account.get_username() << std::endl;
  std::cout << "Password: \t" << account.get_password() << std::endl;

  // saved accounts receive date info
  // checks if the account is new yet unsaved (no date_created, date_mod)
  if (account.get_datecreated() != "") {
    std::cout << "Date created: \t" << account.get_datecreated() << std::endl;
    std::cout << "Date modified: \t" << account.get_datemodified() << std::endl;
  }
}

// loads account using cereal
void AmphoraBackend::LoadAccountList()
{
  // might be better to have filename as an arg?
  std::string filename = "vault.xml";
  // check if filename is in the pwd
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
      Account temp;
      archive( temp );
      accountlist_m.push_back(temp);
    }
      std::cout << "DEBUG: num_saved = " << num_saved << std::endl;
  }

}

// saves account using cereal serialization library
void AmphoraBackend::SaveAccountList(Account &newaccount)
{

  std::string date = amphora_util_m.CurrentDate();
  newaccount.set_datecreated(date);
  newaccount.set_datemodified(date);
  accountlist_m.push_back(newaccount);

  std::string savedaccount = "vault.xml";
  std::size_t num_saved;
  std::cout << "NUMBER BEING SAVED" << accountlist_m.size() << std::endl;
  {
    std::ofstream file( savedaccount );
    cereal::XMLOutputArchive archive( file );

    // store the number of saved accounts in the first location
    num_saved = accountlist_m.size();
    archive( num_saved );
    // put each account into the archive
    // create iterator which is a pointer to objs in vector accountlist
    for ( auto it = std::begin(accountlist_m); it != std::end(accountlist_m); ++it) {
      archive( *it );
    }
  } // when archive goes out of scope it is guaranteed to have flushed its
    // contents to its stream
}

void AmphoraBackend::ViewAccountList(std::string &format, std::string &sortstyle)
{
  //format "short" displays up to the 5 most recent accounts saved in the vault
  //format "long" displays all of the accounts in a given sort - default sort is by acct purpose

  std::cout << std::endl << "Your Saved Accounts:" << std::endl;
  std::vector<std::string> accountnamelist;
  std::size_t largestaccountname = 0;
  // sort accountlist_m before displaying

  // get names from account objects
  if( format == "long" ) {
    for ( auto it = std::begin(accountlist_m); it != std::end(accountlist_m); ++it) {
      std::string accountname = it->get_name();
      accountnamelist.push_back(accountname);
    }
  }

  // displays first 5 accounts stored in accountlist_m
  // sorts by most recently modified!!
  else if (format == "short") {
    int i = 0;
    for ( auto it = std::begin(accountlist_m); it != std::end(accountlist_m); ++it,++i) {
      if ( i < 5 ) {
        std::cout << it->get_name() << std::endl;
        accountnamelist.push_back(accountname);
      }
    }
  }

  amphora_util_m.PrettyTable(accountnamelist);
}
