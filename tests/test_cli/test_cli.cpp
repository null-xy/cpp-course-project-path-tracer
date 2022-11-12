#include "cli.hpp"

int main(int argc, char *argv[]) {
  Tracey::CLI cli;
  bool success = cli.parse_args(argc, argv);
  return (success) ? 0 : 1;
}
