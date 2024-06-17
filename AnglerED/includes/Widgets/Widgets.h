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
        ImGuiTreeNodeFlags flags;
        SceneManager::SceneManager *m_scene;
        void Draw(DS::ENode *);

      public:
        WSceneViewer(std::string);
        void SetScene(SceneManager::SceneManager *);
        void Render() override;
    };

    class WSettings : public UIWidget
    {
      private:
        SceneManager::SceneManager *m_scene;
        ImGuiTreeNodeFlags flags;

      public:
        WSettings(std::string);
        void SetScene(SceneManager::SceneManager *);
        void Render() override;
    };

    class WInfo : public UIWidget
    {
      public:
        WInfo(std::string);
        void Render() override;
    };

    void WTransform(DS::Transform *);
    void WMeshRenderer(GLEngine::MeshRenderer* );
    static void DrawVec3Controls(const std::string &, glm::vec3&);
} // namespace UIEngine
