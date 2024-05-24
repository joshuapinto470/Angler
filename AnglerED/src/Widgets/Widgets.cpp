#include "imgui.h"
#include <Widgets.h>

namespace UIEngine
{

    // Viewport widget
    ViewportWidget::ViewportWidget(std::string title)
    {
        m_uiTitle = title;
        framebuffer.Init(1280, 720);
    }

    // This should be a scene
    // this is just for testing for now.
    void ViewportWidget::SetScene(SceneManager::SceneManager *scene)
    {
        m_scene = scene;
    }

    void ViewportWidget::Render()
    {

        ImGui::Begin(m_uiTitle.c_str());
        if (!m_scene)
        {
            ImGui::Text("No scene selected");
            ImGui::End();
            return;
        }

        float w = ImGui::GetContentRegionAvail().x;
        float h = ImGui::GetContentRegionAvail().y;

        ImVec2 pos = ImGui::GetCursorScreenPos();
        framebuffer.RescaleBuffer(w, h);
        glViewport(0, 0, w, h);
        ImGui::GetWindowDrawList()->AddImage(reinterpret_cast<ImTextureID>(framebuffer.getTexture()),
                                             ImVec2(pos.x, pos.y), ImVec2(pos.x + w, pos.y + h), ImVec2(0, 1),
                                             ImVec2(1, 0));

        ImGui::End();

        framebuffer.Clear();
        framebuffer.Bind();
        m_scene->Render();
        framebuffer.Unbind();
    }

    // Settings widget
    WSettings::WSettings(std::string title)
    {
        m_uiTitle = title;
    }

    void WSettings::Render()
    {
        ImGui::Begin(m_uiTitle.c_str());
        WTransform();
        ImGui::End();
    }

    // Info Widget
    WInfo::WInfo(std::string title)
    {
        m_uiTitle = title;
    }

    void WInfo::Render()
    {
        // ImGui::Begin(m_uiTitle.c_str());
        ImGui::ShowDemoWindow();
        // ImGui::End();
    }

    // Sceneviewer widget

    WSceneViewer::WSceneViewer(std::string name)
    {
        m_uiTitle = name;
        m_scene = nullptr;
    }

    void WSceneViewer::SetScene(SceneManager::SceneManager *scene)
    {
        m_scene = scene;
    }

    void WSceneViewer::Draw(const DS::ENode *node)
    {
        if (ImGui::TreeNode((void *)node, "%s", node->getName().c_str()))
        {
            if (node->isLeaf())
            {
                ImGui::Text("Leaf");
                ImGui::TreePop();
                return;
            }
            for (const auto child : node->getChildren())
                Draw(child);
            ImGui::TreePop();
        }
    }

    void WSceneViewer::Render()
    {
        ImGui::Begin(m_uiTitle.c_str());
        if (m_scene == nullptr)
        {
            ImGui::Text("No scene set!");
            ImGui::End();
            return;
        }
        // This is recursive
        // TODO: Change it to non-recursive
        // https://www.reddit.com/r/cpp_questions/comments/x0ypqt/imgui_tree_view_implementation/
        Draw(m_scene->getRootNode());
        ImGui::End();
    }

    void WTransform()
    {
        glm::vec3 x(1.0f);

        DrawVec3Controls("Transform", x);
        DrawVec3Controls("Rotation", x);
        DrawVec3Controls("Scale", x);
    }

    static void DrawVec3Controls(const std::string &label, glm::vec3 value)
    {
        ImGui::PushID(label.c_str());
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, 100.0f);
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();
        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});

        float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 buttonSize = {lineHeight + 3.0f, lineHeight};

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));

        if (ImGui::Button("X", buttonSize))
            value.x = 0.0f;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &value.x, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.3f, 1.0f));

        if (ImGui::Button("Y", buttonSize))
            value.y = 0.0f;

        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &value.y, 0.1f);
        ImGui::PopItemWidth();
        ImGui::SameLine();

        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.3f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));

        if (ImGui::Button("Z", buttonSize))
            value.z = 0.0f;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &value.z, 0.1f);
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();
        ImGui::Columns(1);
        ImGui::PopID();
    }
} // namespace UIEngine
