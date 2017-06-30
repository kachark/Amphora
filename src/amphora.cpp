//Amphora main file


#include "amphora_interface.hpp"


int main( int argc, const char* argv[] )
{
  AmphoraInterface interface;
  // maybe have an exit flag for interface
  // exit point is in main if these interface methods drop out early, then
  // return 0 will cleanly exit program
  interface.Start();

  return 0;
}





