#pragma once
#include <pch.h>
#include <WindowManager.h>

namespace UIEngine
{
    class UIEngine
    {
    public:
        UIEngine() : m_docking(false){};
        UIEngine(bool);
        ~UIEngine();
        void UIShutdown();
        void Init(jWindowManager::IWindow &) const;
        void StartUI() const;
        void EndUI();

    private:
        bool m_docking;
    };

    class UIWidget
    {
    public:
        virtual void Render() = 0;

    protected:
        std::string m_uiTitle;
    };

} // namespace UIEngine
