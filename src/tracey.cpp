#include <iostream>

#include "tracey.hpp"

int main(int argc, char *argv[]) {
  std::cout << "Tracey - The Next Generation Path Tracer" << std::endl;

  (void)argc;
  (void)argv;

  // Some preliminary boilerplate code how things could go

  // 1. Create command line interface
  // Tracey::CLI cli;

  // 2. Parse command line arguments
  // cli.parse_args(int argc, char *argv[]);

  // 3. create input file parser
  // Tracey::FileParser parser(cli.get_input_file());

  // 4. create scene
  // Tracey::Scene scene;

  // 5. use parser to populate scene with objects
  // Tracey::Scene::from_parser(scene, parser);

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
