#include <filesystem>
#include <iostream>
#include <memory>

#include "tracey.hpp"

namespace Tracey {

class Scene {};

} // namespace Tracey

int main(int argc, char *argv[]) {
  std::cout << "Tracey - The Next Generation Path Tracer" << std::endl;

  // 1. Create command line interface
  Tracey::CLI cli;

  // 2. Parse command line arguments
  if (!cli.parse_args(argc, argv)) return 1;
  std::cout << "Reading input file " << cli.get_input_file() << std::endl;

  // 3. create input file parser, detect file format from file extension
  auto reader = Tracey::FileReader::create(cli.get_input_file());
  if (!reader) return 1;
  std::cout << "FileReader is " << reader->get_name() << std::endl;

  // 4. create scene
  Tracey::Scene scene;

  // 5. populate scene with objects using reader
  // Tracey::Scene::from_reader(scene, reader);

  // 6. create path tracer
  // Tracey::PathTracer path_tracer;

  // 7. create result object
  // Tracey::Result result;

  // 8. render scene using path tracer
  // Tracey::PathTracer::render(result, path_tracer, scene);

  // 9. create output file writer
  // Tracey::FileWriter writer(cli.get_output_file());

  // 10. write result to file using writer
  // writer.write(result);

  return 0;
}
