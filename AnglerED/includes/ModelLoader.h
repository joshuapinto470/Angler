#pragma once

#include <Model.h>
#include <string>
#include "spdlog/spdlog.h"

class ModelLoader
{
private:
public:
    ModelLoader();
    Model LoadModel(std :: string);
    ~ModelLoader();
};