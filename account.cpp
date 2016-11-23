


//implementation of account class

#include "account.hpp"

// Account method definitions
void Account::set_name(std::string name)
{
	Account::m_name = name;
}

void Account::set_purpose(std::string purpose)
{
	Account::m_purpose = purpose;
}

void Account::set_username(std::string username)
{
	Account::m_username = username;
}

void Account::set_password(std::string password)
{
	Account::m_password = password;
}

void Account::set_datecreated(std::string date)
{
	Account::m_datecreated = date;
}

void Account::set_datemodified(std::string date)
{
	Account::m_datemodified = date;
}

std::string Account::get_name()
{
	return Account::m_name;
}

std::string Account::get_purpose()
{
	return Account::m_purpose;
}

std::string Account::get_username()
{
	return Account::m_username;
}

std::string Account::get_password()
{
	return Account::m_password;
}

std::string Account::get_datecreated()
{
	return Account::m_datecreated;
}

std::string Account::get_datemodified()
{
	return Account::m_datemodified;
}


