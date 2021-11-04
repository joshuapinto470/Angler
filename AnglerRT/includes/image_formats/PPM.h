//
// Created by Joshua on 20-06-2021.
//
#pragma once

#include "ImageHandler.h"

class PPM : Image {
  private:
    char *buffer{ nullptr };         // HEAD pointer to buffer
    char *buffer_pointer{ nullptr }; // current pointer in buffer
    char *data_pointer{ nullptr };   // pointer where data starts.
    std::ofstream File;
    unsigned HEIGHT, WIDTH;

  public:
    PPM();
    PPM(const char *, int, int);
    PPM(const Image &);
    ~PPM();

    void WriteHeader();
    void Write(const Color &) override;
    unsigned getHeight() const override;
    unsigned getWidth() const override;
};