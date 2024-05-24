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
} // namespace UIEngine
