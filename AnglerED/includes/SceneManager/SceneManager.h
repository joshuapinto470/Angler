#pragma once

#include <pch.h>
#include <GLEngine.h>
#include <Model.h>

namespace SceneManager
{
    class SceneManager
    {
    private:
        std::vector<Model>* p_modelObjects;
    public:
        SceneManager(/* args */) : p_modelObjects(nullptr) {};
        ~SceneManager();
    };
} // namespace SceneManager
