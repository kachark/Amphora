
// implementation of account.hpp
#include "account_util.hpp"

using namespace boost::posix_time;


// ------ helper funciton definitions
namespace account_util {

	// sets first-time account member information
	void create_account(Account &account)
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

		date = account_util::current_date();
		account.set_datecreated(date);
		account.set_datemodified(date);
	}

	// edit account information
	// make sure to ask user to enter password twice to make sure they entered correctly
	void edit_account(Account &account)
	{
		std::string user;
		bool editing = true;
		while (editing) {
			account_util::view_account(account);
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
	void view_account(Account &account)
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


	// retrieves system date and time in nice format
	std::string current_date()
	{
		time_facet *facet = new time_facet("%d-%b-%Y %H:%M:%S");
		std::cout.imbue(std::locale(std::cout.getloc(), facet));
		//	cout << second_clock::local_time() << endl;
		std::string date = to_simple_string(second_clock::local_time());
		std::cout << "INSIDE get_date() -> " << date << std::endl;
		return date;
	}


	// loads account using cereal serialization library
	std::vector<Account> load_accounts()
	{
		std::vector<Account> accountlist;
		std::string filename = "vault.xml";
    std::size_t num_saved;
		{
			// open stream
			std::ifstream is(filename);
			cereal::XMLInputArchive archive(is);
			// call archive and get number of saved accounts from archive's first index.
      archive( num_saved );
			// loop and call archive for the number of saved accounts, to ensure every account is retrieved.
      for ( auto i = 0; i < num_saved; ++i ) {
        Account temp;
        archive( temp );
        accountlist.push_back(temp);
      }
        std::cout << "num_saved = " << num_saved;
		}
		return accountlist;
	}


	// saves account using cereal serialization library
	// save_account takes in vector of accounts including the new account that was added
	void save_accounts(std::vector<Account> &accountlist)
	{
		std::string savedaccount = "vault.xml";
		std::size_t num_saved;
		{
			std::ofstream file( savedaccount );
			cereal::XMLOutputArchive archive( file );

			// store the number of saved accounts in the first location
			num_saved = accountlist.size();
			archive( num_saved );
			// put each account into the archive
			// create iterator which is a pointer to objs in vector accountlist
			for ( auto it = std::begin(accountlist); it != std::end(accountlist); ++it) {
				archive( *it );
			}
		} // when archive goes out of scope it is guaranteed to have flushed its
		  // contents to its stream
	}


	// encrypts account information
	void encrypt()
	{
		std::cout << "inside encrypt";
	}

	//void sort_accounts( <pass vector of accounts?>, <<sorting parameters>> );
}




