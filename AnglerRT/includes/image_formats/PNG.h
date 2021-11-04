#pragma once

#include "ImageHandler.h"
#include "lodepng.h"

#include <vector>

class PNG : public Image {

  public:
    PNG() = default;
    PNG(const char *FileName, unsigned w, unsigned h);
    PNG(const Image &image);
    ~PNG();

    void SaveFile();
    void GammaCorrect();
    void Write(const Color &) override;
    unsigned getHeight() const override;
    unsigned getWidth() const override;
    std::unique_ptr<uint8_t[]> getBufferCopy() const override;

  private:
    std ::unique_ptr<uint8_t[]> buffer;
    const char *fileName;
    unsigned Width, Height;
    unsigned i;
};