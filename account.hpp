
#ifndef __ACCOUNT_HPP_INCLUDED__
#define __ACCOUNT_HPP_INCLUDED__


// needs cereal headers here so it knows about Archive class etc.
// this gets passed to account_util_new.cpp through account_util_new.hpp

//#include "aes.h"
#include "cereal/archives/xml.hpp" // serialize in xml format
#include <cereal/types/string.hpp>



class Account {

	public:
	// default constructor preferred for serialization
	Account() = default;
	//Account() = {};

	void set_name(std::string name);
	void set_purpose(std::string purpose);
	void set_username(std::string username);
	void set_password(std::string password);
	void set_datecreated(std::string date);
	void set_datemodified(std::string date);
	void set_account_info(Account &account);
	std::string get_name();
	std::string get_purpose();
	std::string get_username();
	std::string get_password();
	std::string get_datecreated();
	std::string get_datemodified();


	// this method lets cereal know which data members to serialize for this type
	template <class Archive>
	void serialize(Archive & ar)
	{
		// serialize things by passing the to the archive
		ar( Account::m_name, Account::m_purpose, Account::m_username, Account::m_password, Account::m_datecreated, Account::m_datemodified );
	}

	private:
	std::string m_name, m_purpose, m_username, m_password, m_datecreated, m_datemodified;

};

#endif





