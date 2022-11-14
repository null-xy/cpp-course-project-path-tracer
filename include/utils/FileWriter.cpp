#include <iostream>
#include "FileWriter.hpp"

FileWriter::FileWriter(std::vector<std::vector<Vector3f>> image)
    : image_(image) {}

FileWriter::~FileWriter() {
    image_.clear();
}

//casts the vector of floats into a valid color composed of 3 hex values
void FileWriter::WritePixel(std::ostream& os, Vector3f color) {
    int r = static_cast<int>(255.999 * color(0));
    int g = static_cast<int>(255.999 * color(1));
    int b = static_cast<int>(255.999 * color(2));

    os << r << ' ' << g << ' ' << b << '\n';
}

// writes the image vector to standard output according to ppm file format
void FileWriter::WriteFile() {

    unsigned int width = image_[0].size();
    unsigned int height = image_.size(); 

    std::cout << "P3\n" << width << ' ' << height << "\n255\n";

    for(int j = height - 1; j >= 0; j--) {
        for (int i = 0; i < width; i++) {
            Vector3f pixel = image_[j][i];
            WritePixel(std::cout, pixel);
        }
    }
}