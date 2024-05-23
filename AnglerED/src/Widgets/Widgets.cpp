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
    void ViewportWidget::SetScene(Model *model)
    {
        m_Model = model;
    }

    void ViewportWidget::Render()
    {

        ImGui::Begin(m_uiTitle.c_str());

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
        m_Model->Draw();
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
        ImGui::End();
    }

    // Info Widget
    WInfo::WInfo(std::string title)
    {
        m_uiTitle = title;
    }

    void WInfo::Render()
    {
        ImGui::Begin(m_uiTitle.c_str());
        ImGui::ShowDemoWindow();
        ImGui::End();
    }
} // namespace UIEngine
