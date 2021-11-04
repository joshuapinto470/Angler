#include "ImageBuffer.h"

ImageBuffer::ImageBuffer(int width, int height) {
    unsigned size = width * height * 4;
    WIDTH = width;
    HEIGHT = height;
    mBuffer = std::make_unique<uint8_t[]>(size);
    buffer_index = 0;
}

ImageBuffer::~ImageBuffer() {
}

void ImageBuffer::Write(const Color &color) {
    auto R = (uint8_t)(color.x() * 255.0f);
    auto G = (uint8_t)(color.y() * 255.0f);
    auto B = (uint8_t)(color.z() * 255.0f);

    mBuffer[buffer_index++] = R;
    mBuffer[buffer_index++] = G;
    mBuffer[buffer_index++] = B;
    mBuffer[buffer_index++] = 255;
}

std::unique_ptr<uint8_t[]> ImageBuffer::getBufferCopy() const {
    std::unique_ptr<uint8_t[]> cBuffer = std::make_unique<uint8_t[]>(WIDTH * HEIGHT * 4);
    for (int i = 0; i < WIDTH * HEIGHT * 4; i++) {
        cBuffer[i] = mBuffer[i];
    }

    return cBuffer;
}