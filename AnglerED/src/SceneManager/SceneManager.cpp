#include <SceneManager.h>

namespace SceneManager
{

    using DS::Transform;
    using GLEngine::MeshRenderer;

    DS::ENode *SceneManager::deepCopy(const MeshNode *node)
    {
        meshNode mesh = node->getEntity();
        std::vector<unsigned> meshIndices = mesh.m_meshIndices;
        MeshFilter filter;
        MeshFilter mesh_pool = m_meshBucket.back();

        for (const auto &i : meshIndices)
        {
            filter.m_meshes.push_back(mesh_pool.m_meshes[i]);
        }

        entt::entity m = m_registry.create();
        m_registry.emplace<Transform>(m, mesh.m_transformation);
        m_registry.emplace<MeshRenderer>(m, filter);

        DS::ENode *_node = new DS::ENode(m);
        _node->setName(node->getName().c_str());

        for (const auto &i : node->getChildren())
        {
            _node->addChild(deepCopy(i));
        }

        return _node;
    }

    SceneManager::SceneManager()
    {
        m_currActive = nullptr;
        // This is a weird workaround for now
        const auto &e = m_registry.create();
        m_registry.destroy(e);
        defaultShader = Shader("/home/joshua/Projects/Angler/AnglerED/shaders/base.vert",
                               "/home/joshua/Projects/Angler/AnglerED/shaders/base.frag");

        name = "Scene 1";
        DS::ENode *root = m_sceneGraph.getRootNode();
        root->setName(name);
    }

    SceneManager::~SceneManager()
    {
        m_currActive = nullptr;
    }

    void SceneManager::setActiveNode(DS::ENode *node)
    {
        m_currActive = node;
    }

    DS::ENode *SceneManager::getActiveNode()
    {
        return m_currActive;
    }

    void SceneManager::Render()
    {
        BENCHMARK_SCOPE

        DS::ENode *root = m_sceneGraph.getRootNode();

        std::vector<DS::ENode *> stack;
        stack.push_back(root);
        while (!stack.empty())
        {
            DS::ENode *node = stack.back();
            stack.pop_back();

            if (node->checkFlag(DS::NODE_FLAGS::HIDDEN))
            {
                continue;
            }

            entt::entity e = node->getEntity();

            /* get parent transform if it exists */
            DS::ENode const *parent = node->getParent();

            Transform p_transform;

            if (parent)
            {
                entt::entity parent_entity = parent->getEntity();
                auto parent_transform = m_registry.try_get<Transform>(parent_entity);
                p_transform = parent_transform ? *parent_transform : p_transform;
            }

            auto renderer = m_registry.try_get<MeshRenderer>(e);
            auto transform = m_registry.try_get<Transform>(e);
            if (transform)
                defaultShader.setMat4("model", transform->transform * p_transform.transform);

            if (renderer)
            {
                for (const auto &i : renderer->getVbo())
                {
                    i.Bind();
                    i.Render();
                    i.Unbind();
                }
            }

            for (const auto &c : node->getChildren())
            {
                stack.push_back(c);
            }
        }
    }

    void SceneManager::Add(const Model &model, DS::ENode *node)
    {
        BENCHMARK_SCOPE
        if (model.m_mesh.m_meshes.empty())
        {
            // For now don't make a node for models with no data
            spdlog::warn("SCENE MANAGER {}", "Model has no mesh data");
            return;
        }

        std::shared_ptr<MeshNode> meshNode = model.m_root;
        MeshFilter filter = model.m_mesh;
        GLEngine::MaterialDataList materials = model.m_materials;
        GLEngine::TextureList textures = model.m_textures;
        m_meshBucket.push_back(filter);

        DS::ENode *copiedNode = deepCopy(meshNode.get());

        DS::ENode *_n = node ? node : m_sceneGraph.getRootNode();
        _n->addChild(copiedNode);

        /*
        for (unsigned i = 0; i < filter.m_meshes.size(); i++)
        {
            GLMesh mesh = filter.m_meshes[i];
            std::string name = mesh.m_name;

            const auto &entity = m_registry.create();

            m_registry.emplace<Transform>(entity);
            // m_registry.emplace<MeshData>(entity, mesh.m_mesh);
            m_registry.emplace<MeshRenderer>(entity, filter);

            DS::ENode *n = new DS::ENode(entity);
            n->setName(name.c_str());
            DS::ENode *_n = node ? node : m_sceneGraph.getRootNode();
            _n->addChild(n);
        }
        */
    }

    void SceneManager::Add(GLEngine::Camera &camera, DS::ENode *node)
    {
        const auto &entity = m_registry.create();
        m_registry.emplace<GLEngine::Camera>(entity, camera);

        DS::ENode *n = new DS::ENode(entity);
        n->setName("Camera");

        DS::ENode *_n = node ? node : m_sceneGraph.getRootNode();
        _n->addChild(n);
    }

    void SceneManager::Add(GLEngine::Light &light, DS::ENode *node)
    {
    }

} // namespace SceneManager

namespace SceneManager
{
    DS::Node<entt::entity> *SceneGraph::getRootNode()
    {
        return m_node;
    }

    SceneGraph::SceneGraph()
    {
        m_node = new DS::ENode();
    }

    SceneGraph::~SceneGraph()
    {
        delete m_node;
    }
} // namespace SceneManager
