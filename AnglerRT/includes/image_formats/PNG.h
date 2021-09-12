#pragma once

#include "ImageHandler.h"
#include "lodepng.h"

#include <vector>

class PNG : public Image {
private:
    std :: vector<uint8_t> buffer;
    const char* fileName{};
    unsigned Width{}, Height{};
public:
    PNG() = default;
    explicit PNG(const char* FileName, unsigned w, unsigned h);
    void GammaCorrect();
    ~PNG();
    void Write(const Color &) override;

    std::vector<uint8_t> getBuffer(){
        return buffer;
    } 
};