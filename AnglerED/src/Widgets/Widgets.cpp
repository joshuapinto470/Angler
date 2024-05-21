#include "imgui.h"
#include <Widgets.h>

namespace UIEngine
{

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

    void WSettings::Render()
    {
        ImGui::Begin(m_uiTitle.c_str());
        ImGui::End();
    }

    WSettings::WSettings(std::string title)
    {
        m_uiTitle = title;
    }

    WInfo::WInfo(std::string title)
    {
        m_uiTitle = title;
    }

    void WInfo::Render()
    {

    }
} // namespace UIEngine
