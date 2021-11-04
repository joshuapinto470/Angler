//
// Created by Joshua on 20-06-2021.
//

#include "PPM.h"

PPM::PPM() : File("Default.ppm", std::ios_base::binary) {
    WIDTH = 255;
    HEIGHT = 255;
    WriteHeader();
}

PPM::PPM(const char *fileName, int _width, int _height) : File(fileName, std::ios_base::binary) {
    WIDTH = _width;
    HEIGHT = _height;
    WriteHeader();
}

PPM::PPM(const Image &image) {
    WIDTH = image.getWidth();
    HEIGHT = image.getHeight();
    buffer = nullptr;
    spdlog::warn("PPM image is currently not fully implemented for Image constructor");
}

PPM::~PPM() {
    // Gamma correct
    for (char *p = data_pointer; p != buffer_pointer; p++) {
        double t = (int)(unsigned char)*data_pointer / 255.0;
        t = sqrt(t);
        *data_pointer = (int)(t * 255);
        ++data_pointer;
    }

    File.write(buffer, (WIDTH * HEIGHT * 3) + 16);
    File.close();

    delete[] buffer;
}

void PPM ::WriteHeader() {
    buffer = new char[(WIDTH * HEIGHT * 3) + 16];
    buffer_pointer = buffer;
    int p = 0;
    p = snprintf(buffer, 4, "P6\n");
    buffer_pointer += p;
    p = snprintf(buffer_pointer, 15, "%d %d\n%d\n", WIDTH, HEIGHT, 255);
    buffer_pointer += p;
    data_pointer = buffer_pointer;
}

void PPM ::Write(const Color &color) {
    *buffer_pointer++ = static_cast<int>(Clamp(color.x() * 255, 0.0, 254.999));
    *buffer_pointer++ = static_cast<int>(Clamp(color.y() * 255, 0.0, 254.999));
    *buffer_pointer++ = static_cast<int>(Clamp(color.z() * 255, 0.0, 254.999));
}

unsigned PPM::getHeight() const {
    return HEIGHT;
}

unsigned PPM::getWidth() const {
    return WIDTH;
}