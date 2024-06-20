#pragma once

#include <pch.h>
#include <map>
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
        DS::ENode *m_node = nullptr;
    };

    class SceneManager
    {
      private:
        SceneGraph m_sceneGraph{};
        GLRenderer::Renderer m_renderer{};
        entt::registry m_registry;

        // Scene state
        DS::ENode *m_currActive;
        std::vector<MeshFilter> m_meshBucket;
        std::vector<GLEngine::TextureList> m_textureBucket;
        std::vector<GLEngine::MaterialList> m_materialBucket;
        std::map<std::string, Shader> m_shaders;
        std::map<std::string, GLEngine::Camera> m_cameraBucket;

        std::string m_name;

        DS::ENode *deepCopy(const MeshNode *);

      public:        
        explicit SceneManager(const char*);
        ~SceneManager();
        void Render();
        void Init();
        void Add(const Model &, DS::ENode *);
        void Add(GLEngine::Light &, DS::ENode *);
        void Add(GLEngine::Camera &, DS::ENode *);
        void setActiveNode(DS::ENode *);
        DS::ENode *getActiveNode();

        DS::ENode *getRootNode()
        {
            return m_sceneGraph.getRootNode();
        };

        Shader getDefaultShader()
        {
          return m_shaders["default_shader"];
        }

        template <class T> T *getComponent(DS::ENode *e)
        {
            if (!e)
                return nullptr;
            return m_registry.try_get<T>(e->getEntity());
        }
    };

} // namespace SceneManager
