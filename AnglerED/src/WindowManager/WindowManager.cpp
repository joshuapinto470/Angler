#include <WindowManager.h>

namespace jWindowManager
{
    static void glfw_error_callback(int error, const char *description)
    {
        spdlog::error("WINDOW MANAGER Code: %d {}", error, description);
    }

    static void glfw_fb_resize_callback(GLFWwindow* window, int w, int h)
    {
        auto p_window = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        p_window->SetScreenDim(w, h);
        glViewport(0, 0, w, h);
    }

    WindowManager::~WindowManager()
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
        glfwTerminate();
    }

    int WindowManager::Init(unsigned WIDTH, unsigned HEIGHT, const char *title)
    {
        if (!glfwInit())
        {
            spdlog::error("WINDOW MANAGER {}", "Failed to initialize GLFW");
            return -1;
        }

        HEIGHT = HEIGHT;
        WIDTH = WIDTH;
        Title = title;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_SAMPLES, 4); // MSAA

        m_window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);

        if (!m_window)
        {
            spdlog::error("WINDOW MANAGER {}", "Failed to create window.");
            return -1;
        }

        glfwMakeContextCurrent(m_window);
        glfwSetWindowUserPointer(m_window, static_cast<void *>(this));

        glfwSetFramebufferSizeCallback(m_window, glfw_fb_resize_callback);
        glfwSetErrorCallback(glfw_error_callback);

        gladLoadGL();

        return 0;
    }

    void WindowManager::SetScreenDim(unsigned W, unsigned H)
    {
        WIDTH = W;
        HEIGHT = H;
    }

    vec2u WindowManager::GetScreenDim()
    {
        return vec2u(WIDTH, HEIGHT);
    }

    int WindowManager::CloseWindow()
    {
        return glfwWindowShouldClose(m_window);
    }

    void WindowManager::PrepareNextFrame()
    {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    void* WindowManager::getWindowCtx()
    {
        return m_window;
    }

} // namespace jWindowManager
