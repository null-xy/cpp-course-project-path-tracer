#include "cli.hpp"

#include <iostream>

using namespace std;
using namespace Tracey;

int main(int argc, char *argv[]) {
  CLI cli;
  bool success = cli.parse_args(argc, argv);
  if (success) {
    cout << "command line arguments parsed succesfully!" << endl;
    cout << "input file = " << cli.get_input_file() << endl;
    cout << "output file = " << cli.get_output_file() << endl;
  } else {
    cout << "\ncommand line arguments parsing failed!" << endl;
  }
  return 0;
}
