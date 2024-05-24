#pragma once

#include <UIEngine.h>
#include <GLEngine.h>

#include <GLModel.h>
#include <SceneManager.h>

namespace UIEngine
{
    class Transform : public UIWidget
    {
    };

    class ViewportWidget : public UIWidget
    {
      private:
        SceneManager::SceneManager *m_scene;
        GLEngine::FrameBuffer framebuffer;

      public:
        ViewportWidget(std::string);
        void SetScene(SceneManager::SceneManager *);
        void Render() override;
    };

    class WSceneViewer : public UIWidget
    {
      private:
        SceneManager::SceneManager *m_scene;
        void Draw(const DS::ENode *);

      public:
        WSceneViewer(std::string);
        void SetScene(SceneManager::SceneManager *);
        void Render() override;
    };

    class WSettings : public UIWidget
    {
      public:
        WSettings(std::string);
        void Render() override;
    };

    class WInfo : public UIWidget
    {
      public:
        WInfo(std::string);
        void Render() override;
    };

    // Renders the transform component.
    void WTransform();
    static void DrawVec3Controls(const std::string &, glm::vec3);
} // namespace UIEngine
