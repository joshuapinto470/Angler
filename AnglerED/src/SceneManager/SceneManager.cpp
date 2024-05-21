#include <SceneManager.h>

namespace SceneManager
{
    SceneManager::SceneManager()
    {
        p_modelObjects = std::vector<Model>();
        p_cameras = std::vector<GLEngine::Camera>();
        p_lights = std::vector<GLEngine::Light>();
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
        p_modelObjects.push_back(model);
    }

    void SceneManager::Add(GLEngine::Camera &camera)
    {
        p_cameras.push_back(camera);
    }

    void SceneManager::Add(GLEngine::Light &light)
    {
        p_lights.push_back(light);
    }
    
} // namespace SceneManager
