#include <SceneManager.h>

namespace SceneManager
{
    SceneManager::~SceneManager()
    {
        if (p_modelObjects)
        {
            delete p_modelObjects;
            p_modelObjects = nullptr;
        }
    }

    void SceneManager::Render()
    {
        
    }
} // namespace SceneManager
