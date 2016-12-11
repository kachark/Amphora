


#ifndef __ACCOUNT_UTIL_HPP_INCLUDED__
#define __ACCOUNT_UTIL_HPP_INCLUDED__


#include "account.hpp"
#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>


namespace account_util {

	// Declare helper functions
	void create_account(Account &newaccount);
	void edit_account(Account &account);
	void view_account(Account &account);
	std::string current_date();
	std::vector<Account> load_accounts(); //pass array of accounts
	void save_accounts(std::vector<Account> &accountlist); //pass array of accounts
	//void sort_accounts( <pass vector of accounts?>, <<sorting parameters>> );
	void encrypt();

}

#endif
