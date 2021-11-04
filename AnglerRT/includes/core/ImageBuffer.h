#pragma once

#include "ImageHandler.h"
#include "Utilities.h"

class ImageBuffer : public Image {
  public:
    ImageBuffer(int, int);
    ~ImageBuffer();
    unsigned getHeight() const override {
        return HEIGHT;
    }
    unsigned getWidth() const override {
        return WIDTH;
    }
    void Write(const Color &) override;
    std::unique_ptr<uint8_t[]> getBufferCopy() const override;

  private:
    unsigned WIDTH, HEIGHT;
    int buffer_index;
    std::unique_ptr<uint8_t[]> mBuffer;
};