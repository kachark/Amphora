//Amphora main file


#include "amphora_interface.hpp"

using std::cout; using std::cin; using std::endl; using std::string; using std::vector;


int main( int argc, const char* argv[] )
{

  string userinput;
  AmphoraInterface interface;

  while(1) {

    cout << "****** MAIN MENU ******\n";

    // User actions
    cout << "\n(1): Add account\n(2): Edit account\n(3): Delete account\n(4): Advanced\n(5): Quit\n\n";

    //LOOK UP CORRECT WAY TO HAVE A MAIN LOOP
    getline(cin, userinput);

    if(userinput == "5") {
      // stuff have to change this actually make it exit
      std::cout << "Exiting App..." << std::endl;
      break;
    }

    else {
      interface.MainMenu(userinput);
    }

  }

  return 0;
}





