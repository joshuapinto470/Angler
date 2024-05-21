#pragma once

#include <GLModel.h>
#include <string>

class ModelLoader
{
private:
public:
    ModelLoader();
    Model LoadModel(std::string);
    ~ModelLoader();
};
