//Amphora main file


#include "account.hpp"
#include "account_util.hpp"

using std::cout; using std::cin; using std::endl; using std::string; using std::vector;


int main( int argc, const char* argv[] )
{

	string mainmenu;
	string line;

  // don't know how many objs are stored in file, so when saving, also include the current size of the list so it can be used to call the archive the correct amount of times
  vector<Account> accountlist = account_util::load_accounts();

  //load accounts in a vector since we don't know how many objs there will be
  //when saving new obj, append the new obj to the array
  //
  //  //test case
  //  vector<account_util::Account> accountlist;
  //  account_util::Account a1, a2;
  //  account_util::create_account(a1);
  //  account_util::create_account(a2);

	cout << "\n*********** Amphora 0.1 ************\n\n";
	cout << "Press enter to continue...\n";

	// Start main menu
	while(getline(cin,line)) {
		cout << "****** MAIN MENU ******\n";
		// --- check for saved accounts and display stats ---
		// User actions
		cout << "\n(1): Add account\n(2): Edit account\n(3): Delete account\n(4): Advanced\n(5): Quit\n\n";
		getline(cin, mainmenu);

		// Add account
		if(mainmenu == "1") {
			string submenu;
			Account newaccount;
			account_util::create_account(newaccount);

      // all account objs created are added to a templist.
      // once user decides to save changes, templist is appended to accountlist which is then passed
      // to account_util::save_accounts()
			while(mainmenu == "1") {
				cout << "\nIs the information correct?\n";
				account_util::view_account(newaccount);
				string temp = " "; // temporary string to enable editing
				cout << "\n(1): Save account\n(2): Edit account\n(3): Return to Main Menu without saving\n";
				getline(cin, submenu);

				// save new account
        // append accountlist with account
        // pass accountlist to be saved once all new accounts have been made
				if(submenu == "1") {
					cout << "Saving account..." << endl;
					string date = account_util::current_date();
					newaccount.set_datecreated(date);
					newaccount.set_datemodified(date);
					accountlist.push_back(newaccount);
          //test case
          //          a1.set_datecreated(date);
          //          a1.set_datemodified(date);
          //          a2.set_datecreated(date);
          //          a2.set_datemodified(date);
          //          accountlist.push_back(a1);
          //          accountlist.push_back(a2);
          //encrypt(newaccount);
					account_util::save_accounts(accountlist);
					mainmenu = "";
				}

				// MAKE SURE PROMPTS MAKE SENSE
				// edit new account before saving
				else if(submenu == "2") {
					cout << "\n****** Editing account..." << endl;
					account_util::edit_account(newaccount);
				}

				//return to mainmenu without creating new account
				else if(submenu == "3") {
				  cout << "\nReturning to Main Menu...\n";
				  break;
				}
        vector<Account> accountlist = account_util::load_accounts();
			}
		}

		// edit existing account
		else if(mainmenu == "2") { // edit account
			//list the accounts in nice tabular format, and allow the user to select the one that they want to edit.
		}

		// delete account
		else if(mainmenu == "3") {
      //go into the xml file and delete the necessary index
		}

		// Advanced optios (TBD)
		else if(mainmenu == "4") {
			//choose encryption options, fingerprint scanner support, secure password generator etc.
		}
		else if(mainmenu == "5") {
			cout << "Quitting..." << endl;
			break;
		}
	}

	return 0;
}





