#pragma once

#include <pch.h>
#include <GLEngine.h>
#include <Model.h>
#include <Renderer.h>

namespace SceneManager
{
    class SceneManager
    {
    private:
        std::vector<Model>* p_modelObjects;
        // std::vector<Camera>* p_cameras;
        // std::vector<Lights>* p_lights;

        GLRenderer::Renderer m_renderer;
    public:
        SceneManager() : p_modelObjects(nullptr) {};
        ~SceneManager();
        void Render();
    };
} // namespace SceneManager
