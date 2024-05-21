#pragma once
#include <pch.h>

namespace jWindowManager
{
    class IWindow
    {
    public:
        virtual void *getWindowCtx() = 0;

    protected:
        unsigned WIDTH, HEIGHT;
        std::string Title;
    };

    class WindowManager : public IWindow
    {
    private:
        GLFWwindow *m_window;

    public:
        WindowManager() : m_window(nullptr){};
        ~WindowManager();

        int Init(unsigned, unsigned, const char *);
        void SetScreenDim(unsigned, unsigned);
        void* getWindowCtx() override;
        vec2u GetScreenDim();
        int CloseWindow();
        void PrepareNextFrame();
    };

} // namespace jWindowManager
