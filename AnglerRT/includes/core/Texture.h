//
// Created by Joshua on 18-06-2021.
//

#pragma once

#include "Utilities.h"
#include <lodepng.h>
#include <vector>

struct Pixel {
    float R, G, B, A;
    Pixel(float r, float g, float b, float a) {
        R = r;
        G = g;
        B = b;
        A = a;
    }
};

class Texture {
  public:
    Texture() = default;
    explicit Texture(const char *);

    Color GetPixel(int, int) const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

  private:
    const char *mFileName{ nullptr };
    bool isValid;
    std ::vector<unsigned char> imageData;
    std ::vector<Pixel> pixelData;
    unsigned width{ 0 }, height{ 0 };
};
