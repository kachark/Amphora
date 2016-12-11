


//implementation of account class

#include "account.hpp"

// Account method definitions
void Account::set_name(std::string &name)
{
  Account::name_m = name;
}

void Account::set_purpose(std::string &purpose)
{
  Account::purpose_m = purpose;
}

void Account::set_username(std::string &username)
{
  Account::username_m = username;
}

void Account::set_password(std::string &password)
{
  Account::password_m = password;
}

void Account::set_datecreated(std::string &date)
{
  Account::datecreated_m = date;
}

void Account::set_datemodified(std::string &date)
{
  Account::datemodified_m = date;
}

std::string Account::get_name()
{
  return Account::name_m;
}

std::string Account::get_purpose()
{
  return Account::purpose_m;
}

std::string Account::get_username()
{
  return Account::username_m;
}

std::string Account::get_password()
{
  return Account::password_m;
}

std::string Account::get_datecreated()
{
  return Account::datecreated_m;
}

std::string Account::get_datemodified()
{
  return Account::datemodified_m;
}


