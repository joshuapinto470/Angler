//
// Created by Joshua on 23-06-2021.
//

#include "Texture.h"

Texture ::Texture(const char *fileName) :
        mFileName(fileName)
{
    unsigned error = lodepng::decode(imageData, width, height, fileName);
    if(error) {
        spdlog::warn("Error loading texture!");
        return;
    }

    pixelData.reserve(width * height);
    for (int i = 0; i < imageData.size(); i = i + 4) {
        unsigned r = imageData[i];
        unsigned g = imageData[i + 1];
        unsigned b = imageData[i + 2];
        unsigned a = imageData[i + 3];
        Pixel pxl(r, g, b, a);
        pixelData.push_back(pxl);
    }
}

Color Texture::GetPixel(int x, int y) const {
    unsigned index = x * height + y;
    if(index > pixelData.size()){
        // This is a bug. index should not be out of bounds of the texture.
        // happens when y < 2. i.e camera pointing up.
        // For now return a black pixel.
        return {0, 0, 0};
    }
    Pixel pxl = pixelData[index];
    return {pxl.R / 255.0f, pxl.G / 255.0f, pxl.B / 255.0f};
}

unsigned int Texture::getWidth() const {
    return width;
}

unsigned int Texture::getHeight() const {
    return height;
}

