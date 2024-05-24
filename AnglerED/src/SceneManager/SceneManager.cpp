#include <SceneManager.h>

namespace SceneManager
{

    using DS::Transform;
    using GLEngine::MeshRenderer;

    SceneManager::SceneManager()
    {
    }

    SceneManager::~SceneManager()
    {
    }

    void SceneManager::Render()
    {

        DS::ENode *root = m_sceneGraph.getRootNode();
        DS::ENode *node;
        std::vector<DS::ENode *> stack;
        stack.push_back(root);
        while (!stack.empty())
        {
            node = stack.back();
            stack.pop_back();

            entt::entity e = node->getEntity();

            auto renderer = m_registry.try_get<MeshRenderer>(e);
            if (renderer)
                renderer->Render();

            for (const auto& c : node->getChildren())
            {
                stack.push_back(c);
            }
        }
    }

    void SceneManager::Add(Model &model, DS::ENode *node)
    {
        const auto &entity = m_registry.create();

        m_registry.emplace<Transform>(entity);
        m_registry.emplace<MeshFilter>(entity, model.getMesh());
        MeshFilter m = m_registry.get<MeshFilter>(entity);
        m_registry.emplace<MeshRenderer>(entity, m);

        DS::ENode *n = new DS::ENode(entity);
        n->setName(model.getMesh().m_meshes[0].m_name);

        DS::ENode *_n = node ? node : m_sceneGraph.getRootNode();
        _n->addChild(n);
    }

    void SceneManager::Add(GLEngine::Camera &camera)
    {
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
        
    }
} // namespace SceneManager
