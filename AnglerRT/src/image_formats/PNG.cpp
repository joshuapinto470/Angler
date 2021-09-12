//
// Created by Joshua on 20-06-2021.
//

#include "PNG.h"

void PNG::Write(const Color &color) {
    auto R = (unsigned char) (color.x() * 255.0f);
    auto G = (unsigned char) (color.y() * 255.0f);
    auto B = (unsigned char) (color.z() * 255.0f);

    buffer.push_back(R);
    buffer.push_back(G);
    buffer.push_back(B);
    buffer.push_back(255);
}

PNG::~PNG() {
    std :: vector<unsigned char> encodedPNG;
    GammaCorrect();
    unsigned error = lodepng::encode(encodedPNG, buffer, Width, Height);
    if(!error) lodepng::save_file(encodedPNG,fileName);
}

PNG::PNG(const char *FileName, unsigned int w, unsigned int h)
:fileName(FileName), Width(w), Height(h){
    buffer.reserve(w * h);
}

void PNG::GammaCorrect() {
    for(auto& i : buffer){
        float t = i / 255.0f;
        t = sqrt(t);
        i = (unsigned char) (t * 255.0f);
    }
}
