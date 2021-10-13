#pragma once

#include "Geometry.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

class Image {
  public:
    virtual void Write(const Color &) = 0;
    virtual std::unique_ptr<uint8_t[]> getBufferCopy() const = 0;
    virtual unsigned getHeight() const = 0;
    virtual unsigned getWidth() const = 0;
};