#pragma once

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

bool BindImageTexture(float *, GLuint *, int, int);


#include <algorithm>
#include <cstdio>
#include <thread>
#include <utility>

#include "AnglerRT.h"
#include "BVH.h"
#include "Render.h"

#include "obj2angler.h"

#include "scenes.h"

class AnglerED {
  private:
    // Display settings
    GLFWwindow *window;
    //ImGuiIO& io;
    GLuint renderedImageTexture = 0;
    int WIDTH, HEIGHT;
    bool needToBindTexture = false;
    int lastPassIndex = 1;

    // Renderer settings
    Render *mRenderer;
    Camera mCamera;
    Options options;
    Scene mWorld;
    //ImGuiIO &io;
    int cameraFOV;
    float aspect_ratio;
    // ImGUI

    int Init();
    void DrawRenderWindow();
    void DrawSceneMenu();
    void DrawSettingsMenu();
    void DrawRenderButton();
    void DrawScenePicker();

  public:
    AnglerED(uint16_t, uint16_t);
    ~AnglerED();

    void Loop();
};