#pragma once

#include "../tracey.hpp"
#include <fstream>

using json = nlohmann::json;

namespace Tracey {

class FileReader {
 public:
  FileReader() : filename_("") {}
  FileReader(const std::string& filename) : filename_{filename} {}

  Tracey::GeometryList read_file(const std::string& filename) {
    filename_ = filename;
    std::ifstream f("example.json");
    json data = json::parse(f);
  }

  std::string get_filename() const {
    return filename_;
  }

 private:
  std::string filename_;
};

}  // namespace Tracey