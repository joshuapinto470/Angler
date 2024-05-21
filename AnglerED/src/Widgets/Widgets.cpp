#include "imgui.h"
#include <Widgets.h>

namespace UIEngine
{

    // Viewport widget
    ViewportWidget::ViewportWidget(std::string title)
    {
        m_uiTitle = title;
    }

    void ViewportWidget::Render()
    {
        ImGui::Begin(m_uiTitle.c_str());
        ImGui::Text("Hello, World!");
        ImGui::End();
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
        ImGui::End();
    }
} // namespace UIEngine
