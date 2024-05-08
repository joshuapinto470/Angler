#pragma once

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>


bool BindImageTexture(float *, GLuint *, int, int);


#include <algorithm>
#include <cstdio>
#include <thread>
#include <utility>

#include "AnglerRT.h"
#include "Render.h"

#include "scenes.h"

#include <Model.h>
#include <ModelLoader.h>
#include <Shader.h>

class AnglerED {
  private:
    // Display settings
    GLFWwindow *window;
    GLuint renderedImageTexture = 0;
    int WIDTH, HEIGHT;
    bool needToBindTexture = false;
    int lastPassIndex = 1;

    // Renderer settings
    Render *mRenderer;
    Camera mCamera;
    Options options;
    Scene mWorld;
    Model mModel;
    int cameraFOV;
    float aspect_ratio;

    int Init();
    void DrawRenderWindow();
    void DrawSceneMenu();
    void DrawSettingsMenu();
    void DrawRenderButton();
    void RenderImGUI();

    static void framebuffer_size_cb(GLFWwindow*, int, int);

  public:
    AnglerED(uint16_t, uint16_t);
    ~AnglerED();

    void Loop();
};