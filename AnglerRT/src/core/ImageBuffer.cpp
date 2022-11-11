#include "ImageBuffer.h"

ImageBuffer::ImageBuffer(int width, int height) {
    unsigned size = width * height * 4;
    WIDTH = width;
    HEIGHT = height;
    mBuffer = std::make_unique<float[]>(size);
    mAccumulateBuffer = std::make_unique<float[]>(size);
    
    for (int i = 0; i < WIDTH * HEIGHT * 4; i++){
        mBuffer[i] = 0.0f;
        mAccumulateBuffer[i] = 0.0f;
    }
    buffer_index = 0;
}

ImageBuffer::~ImageBuffer() {
}

void ImageBuffer::Write(const Color &color) {
    //auto R = (uint8_t)(color.x() * 255.0f);
    //auto G = (uint8_t)(color.y() * 255.0f);
    //auto B = (uint8_t)(color.z() * 255.0f);

    mBuffer[buffer_index++] = color.x();
    mBuffer[buffer_index++] = color.y();
    mBuffer[buffer_index++] = color.z();
    mBuffer[buffer_index++] = 1.0f;
}

void ImageBuffer::WriteAt(const Color &color, int x, int y){
    int index = (x * 4) + y * WIDTH;
    mBuffer[index + 0] = color.x();
    mBuffer[index + 1] = color.y();
    mBuffer[index + 2] = color.z();
    mBuffer[index + 3] = 1.0f;
}

void ImageBuffer::Accumulate(const Color &color, int pass){
    int bufferAccumIndex = buffer_index;

    mBuffer[buffer_index++] += color.x();
    mBuffer[buffer_index++] += color.y();
    mBuffer[buffer_index++] += color.z();
    mBuffer[buffer_index++] = 1.0f;

    mAccumulateBuffer[bufferAccumIndex + 0] = mBuffer[bufferAccumIndex + 0] / pass;
    mAccumulateBuffer[bufferAccumIndex + 1] = mBuffer[bufferAccumIndex + 1] / pass;
    mAccumulateBuffer[bufferAccumIndex + 2] = mBuffer[bufferAccumIndex + 2] / pass;
    mAccumulateBuffer[bufferAccumIndex + 3] = 1.0f;

}

void ImageBuffer::ResetIndex(){
    buffer_index = 0;
}

Color ImageBuffer::ReadAt(int x, int y){
return Color(0, 0, 0);
}

std::unique_ptr<float[]> ImageBuffer::getBufferCopy() const {
    std::unique_ptr<float[]> cBuffer = std::make_unique<float[]>(WIDTH * HEIGHT * 4);
    for (int i = 0; i < WIDTH * HEIGHT * 4; i++) {
        cBuffer[i] = mAccumulateBuffer[i];
    }

    return cBuffer;
}