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
    }

    void SceneManager::Add(Model &model, DS::ENode *node)
    {
        model.initModel();
        const auto &entity = m_registry.create();
        
        m_registry.emplace<Transform>(entity);
        m_registry.emplace<MeshFilter>(entity);
        m_registry.emplace<MeshRenderer>(entity);

        DS::ENode *n = new DS::ENode(entity);

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
} // namespace SceneManager
