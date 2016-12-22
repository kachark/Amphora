//Amphora main file


#include "amphora_interface.hpp"

using std::cout; using std::cin; using std::endl; using std::string; using std::vector;


int main( int argc, const char* argv[] )
{

  string userinput;
  AmphoraInterface interface;

  while(1) {

    cout << "\n\n****** MAIN MENU ******\n";

    // User actions
    cout << "\n(1): Add account\n(2): Edit account\n(3): Delete account\n(4): View Accounts\n(5): Options\n(6): Quit\n\n";

    //LOOK UP CORRECT WAY TO HAVE A MAIN LOOP
    getline(cin, userinput);

    if(userinput == "6") {
      // stuff have to change this actually make it exit
      std::cout << "Exiting App..." << std::endl;
      break;
    } else {
      interface.MainMenu(userinput);
    }

  }

  return 0;
}





