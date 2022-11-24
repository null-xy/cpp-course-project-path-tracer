#include <iostream>
#include <typeinfo>

#include "../include/tracey/tracey.hpp"

using json = nlohmann::json;

int main() {
  Tracey::FileReaderJSON::read_json(
      "/mnt/c/Users/Aleksi/Documents/Koulu/cpp-course-project-path-tracer/include/tracey/utils/example.json");

      return 0;
}