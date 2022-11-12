#pragma once

#include <iostream>

namespace Tracey {

/**
 * @brief Simple command line interface.
 *
 */
class CLI {
private:
  std::string m_input_file;
  std::string m_output_file;

public:
  /**
   * @brief Constructor of command line interface
   *
   * @param argc number of command line arguments
   * @param argv command line arguments
   * @return true if command line arguments are parsed succesfully
   * @return false if something goes wrong
   */
  bool parse_args(int argc, char *argv[]) {
    if (argc != 3) {
      std::cout << "usage: " << argv[0] << " input_file output_file\n\n";
      std::cout << "positional arguments:\n";
      std::cout << " input_file         input file in supported format\n";
      std::cout << " output_file        output file to write results in "
                   "supported format\n";
      return false;
    }
    m_input_file = argv[1];
    m_output_file = argv[2];
    return true;
  }

  /**
   * @brief Get the input file name
   *
   * @return const std::string&
   */
  const std::string &get_input_file() const { return m_input_file; }

  /**
   * @brief Get the output file name
   *
   * @return const std::string&
   */
  const std::string &get_output_file() const { return m_output_file; }
};

} // namespace Tracey
