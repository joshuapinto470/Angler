#include <UIEngine.h>

namespace UIEngine
{
    UIEngine::UIEngine(bool docking)
    {
        m_docking = docking;
    }

    UIEngine::~UIEngine()
    {
    }

    void UIEngine::UIShutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UIEngine::Init(jWindowManager::IWindow &window)
    {
        const char *glsl_version = "#version 130";
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();

        // Enable m_docking
        if (m_docking)
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui::StyleColorsDark();

        io.Fonts->AddFontFromFileTTF("/home/joshua/Projects/Angler/res/fonts/Roboto-Medium.ttf", 14);

        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow *)window.getWindowCtx(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }

    void UIEngine::StartUI()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (m_docking)
            ImGui::DockSpaceOverViewport();
    }

    void UIEngine::EndUI()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} // namespace UIEngine
