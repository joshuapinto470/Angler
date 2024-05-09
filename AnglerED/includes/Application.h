#pragma once

#include <pch.h>
#include <GLEngine.h>
#include <WindowManager.h>

#include <ModelLoader.h>
#include <Model.h>
#include <Shader.h>

class App
{
private:
    GLEngine::GLEngine engine;
    // UIEngine::UIEngine *ui;
    jWindowManager::WindowManager window;

public:
    App();
    void Init();
    void Loop();
};