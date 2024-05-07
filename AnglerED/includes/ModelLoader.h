#pragma once

#include <Model.h>
#include <string>

class ModelLoader
{
private:
public:
    ModelLoader();
    Model LoadModel(std :: string);
    ~ModelLoader();
};