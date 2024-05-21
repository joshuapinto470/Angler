#pragma once

#include <pch.h>
#include <GLEngine.h>
#include <GLModel.h>
#include <Renderer.h>
#include <GLLight.h>
#include <GLCamera.h>

#include <DataStructures.h>

namespace SceneManager
{
    class SceneGraph
    {
      private:
        // The root node of the scene graph.
        DS::Node<int> *m_node;
        DS::Node<int> m_camRef;
    };

    class SceneManager
    {
      private:
        SceneGraph m_sceneGraph;
        GLRenderer::Renderer m_renderer;

      public:
        SceneManager();
        ~SceneManager();
        void Render();
        void Add(Model &);
        void Add(GLEngine::Camera &);
        void Add(GLEngine::Light &);
    };

} // namespace SceneManager
