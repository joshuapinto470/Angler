#pragma once

#include <pch.h>
#include <GLEngine.h>
#include <GLModel.h>
#include <Renderer.h>
#include <GLLight.h>
#include <GLCamera.h>

#include <DataStructures.h>
#include <GLEntity.h>

#include <entt/entity/registry.hpp>

namespace SceneManager
{
    class SceneGraph
    {
      public:
        SceneGraph();
        ~SceneGraph();
        DS::ENode *getRootNode();

      private:
        // The root node of the scene graph.
        DS::ENode *m_node;
    };

    class SceneManager
    {
      private:
        SceneGraph m_sceneGraph;
        GLRenderer::Renderer m_renderer;
        entt::registry m_registry;

        // Scene state
        DS::ENode* m_currSelected;

        std::string name;

      public:
        SceneManager();
        ~SceneManager();
        void Render();
        void Add(Model &, DS::ENode *);
        void Add(GLEngine::Light &, DS::ENode *);
        void Add(GLEngine::Camera &);

        DS::ENode *getRootNode()
        {
            return m_sceneGraph.getRootNode();
        };
    };

} // namespace SceneManager
