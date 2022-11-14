#ifndef PATH_TRACER_FILE_WRITER
#define PATH_TRACER_FILE_WRITER

#include <eigen3/Eigen/Dense>
#include <vector>
 
using Eigen::Vector3f;

class FileWriter {
    public:
        FileWriter(std::vector<std::vector<Vector3f>> image);
        ~FileWriter();
        void WritePixel(std::ostream& os, Vector3f color);
        void WriteFile();

    private:
        std::vector<std::vector<Vector3f>> image_;
};

#endif