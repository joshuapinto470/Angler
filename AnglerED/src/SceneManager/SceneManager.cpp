#include <SceneManager.h>

namespace SceneManager
{
    SceneManager::SceneManager()
    {
    }

    SceneManager::~SceneManager()
    {
    }

    void SceneManager::Render()
    {
    }

    void SceneManager::Add(Model &model)
    {
        model.initModel();
    }

    void SceneManager::Add(GLEngine::Camera &camera)
    {
    }

    void SceneManager::Add(GLEngine::Light &light)
    {
    }
    
} // namespace SceneManager
