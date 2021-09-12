#pragma once

#include "Geometry.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>

class Image{  
    public:
        int width{}, height{};
        virtual void Write(const Color&) = 0;
};