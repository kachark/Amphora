// Amphora main file

#include "cli.hpp"

int main(int argc, const char *argv[]) {
  amphora::cli::AmphoraInterface interface;
  interface.Start();

  return 0;
}
