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
    void WriteAt(const Color &, int x, int y);
    void Accumulate(const Color &, int);
    Color ReadAt(int x, int y);

    void ResetIndex();
    std::unique_ptr<float[]> getBufferCopy() const override;

  private:
    unsigned WIDTH, HEIGHT;
    int buffer_index;
    std::unique_ptr<float[]> mBuffer;
    std::unique_ptr<float[]> mAccumulateBuffer;
};