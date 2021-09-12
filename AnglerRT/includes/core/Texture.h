//
// Created by Joshua on 18-06-2021.
//

#pragma once

#include <lodepng.h>
#include <vector>
#include "Utilities.h"

struct Pixel{
    unsigned R, G, B, A;
    Pixel(unsigned r, unsigned g, unsigned b, unsigned a){
        R = r;
        G = g;
        B = b;
        A = a;
    }
};


class Texture {
public:
    Texture() = default;
    explicit Texture(const char*);

    Color GetPixel(int, int) const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

private:
    const char* mFileName{nullptr};
    std :: vector<unsigned char> imageData;
    std :: vector<Pixel> pixelData;
    unsigned width{0}, height{0};
};


