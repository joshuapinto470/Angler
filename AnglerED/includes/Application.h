#pragma once

#include <pch.h>
#include <GLEngine.h>
#include <UIEngine.h>
#include <WindowManager.h>
#include <Widgets.h>

#include <ModelLoader.h>
#include <GLModel.h>
#include <Shader.h>

class App
{
private:
    GLEngine::GLEngine engine;
    UIEngine::UIEngine ui;
    jWindowManager::WindowManager window;

public:
    App();
    ~App();
    void Init();
    void Loop();
};
