#pragma once

#include <UIEngine.h>
#include <GLEngine.h>

#include <GLModel.h>

namespace UIEngine
{
    class Transform : public UIWidget
    {
    };

    class ViewportWidget : public UIWidget
    {
      private:
        Model *m_Model;
        GLEngine::FrameBuffer framebuffer;
      public:
        ViewportWidget(std::string);
        void SetScene(Model *);
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
