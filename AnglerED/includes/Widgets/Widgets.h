#pragma once

#include <UIEngine.h>
#include <GLEngine.h>

#include <GLModel.h>
#include <GLEntity.h>
#include <SceneManager.h>
#include <DataStructures.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace UIEngine
{
    class ViewportWidget : public UIWidget
    {
      private:
        SceneManager::SceneManager *m_scene{};
        GLEngine::FrameBuffer framebuffer{};
        unsigned m_width{}, m_height{};

      public:
        explicit ViewportWidget(const char *);
        void SetScene(SceneManager::SceneManager *);
        [[nodiscard]] glm::vec2 getViewportDim() const
        {
            return {m_width, m_height};
        };
        void Render() override;
    };

    class WSceneViewer : public UIWidget
    {
      private:
        ImGuiTreeNodeFlags flags;
        SceneManager::SceneManager *m_scene;
        void Draw(DS::ENode *);

      public:
        explicit WSceneViewer(const char *);
        void SetScene(SceneManager::SceneManager *);
        void Render() override;
    };

    class WSettings : public UIWidget
    {
      private:
        SceneManager::SceneManager *m_scene{};
        ImGuiTreeNodeFlags flags;

      public:
        explicit WSettings(const char *);
        void SetScene(SceneManager::SceneManager *);
        void Render() override;
    };

    class WInfo : public UIWidget
    {
      public:
        explicit WInfo(const char *);
        void Render() override;
    };

    void WTransform(DS::Transform *);
    void WMeshRenderer(GLEngine::MeshRenderer *);
    static void DrawVec3Controls(const std::string &, glm::vec3 &);
} // namespace UIEngine
