#pragma once

#include <filesystem>
#include <iostream>
#include <memory>

namespace Tracey {

class FileReader {
public:
  virtual std::string get_name() = 0;

  static std::unique_ptr<FileReader> create(const std::string &filename);
};

class PovFileReader : public FileReader {
private:
  const std::string m_filename;

public:
  PovFileReader(const std::string &filename) : m_filename(filename) {}

  static std::string get_extension() { return ".pov"; }

  std::string get_name() { return "PovFileReader"; }

  std::string get_filename() { return m_filename; }
};

std::unique_ptr<FileReader> FileReader::create(const std::string &filename) {
  std::filesystem::path path(filename);
  std::string file_ext = path.extension();
  if (file_ext == PovFileReader::get_extension())
    return std::make_unique<PovFileReader>(filename);
  std::cerr << "Unknown file format: " << file_ext << std::endl;
  return nullptr;
}

} // namespace Tracey
