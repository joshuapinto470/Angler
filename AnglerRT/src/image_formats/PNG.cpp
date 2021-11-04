//
// Created by Joshua on 20-06-2021.
//

#include "PNG.h"

PNG::PNG(const char *FileName, unsigned int w, unsigned int h) : fileName(FileName), Width(w), Height(h) {
    buffer = std::make_unique<uint8_t[]>(w * h * 4);
}

PNG::PNG(const Image &image) {
    fileName = "TempFile.png";
    Width = image.getWidth();
    Height = image.getHeight();
    buffer = image.getBufferCopy();
}

void PNG::Write(const Color &color) {
    auto R = (uint8_t)(color.x() * 255.0f);
    auto G = (uint8_t)(color.y() * 255.0f);
    auto B = (uint8_t)(color.z() * 255.0f);

    buffer[i++] = R;
    buffer[i++] = G;
    buffer[i++] = B;
    buffer[i++] = 255;
}

unsigned PNG::getWidth() const {
    return Width;
}

unsigned PNG::getHeight() const {
    return Height;
}

void PNG::SaveFile() {
    GammaCorrect();

    std ::vector<uint8_t> encodedPNG;
    std ::vector<uint8_t> tocodePNG;
    tocodePNG.reserve(Width * Height * 4);

    for (int i = 0; i < Width * Height * 4; i++) {
        tocodePNG.push_back(buffer[i]);
    }

    unsigned error = lodepng::encode(encodedPNG, tocodePNG, Width, Height);
    if (!error)
        lodepng::save_file(encodedPNG, fileName);
    else
        spdlog::warn("PNG Savefile error : {}", lodepng_error_text(error));
}

void PNG::GammaCorrect() {
    for (int i = 0; i < Width * Height * 4; i++) {
        Float t = (Float)buffer[i] / 255.0f;
        t = sqrt(t);
        buffer[i] = (uint8_t)(t * 255.0f);
    }
}

std::unique_ptr<uint8_t[]> PNG::getBufferCopy() const {
    std::unique_ptr<uint8_t[]> tBuffer;
    tBuffer = std::make_unique<uint8_t[]>(Width * Height);
    for (int i = 0; i < Width * Height * 4; i++)
        tBuffer[i] = buffer[i];

    return tBuffer;
}

PNG::~PNG() {
    SaveFile();
}