#pragma once

#include <pch.h>

bool BindImageTexture(float *, GLuint *, int, int);
#include "AnglerRT.h"
#include "Render.h"

#include "scenes.h"

#include <Model.h>
#include <ModelLoader.h>
#include <Shader.h>


class AnglerED
{
private:
  // Display settings
  GLFWwindow *window;
  GLuint renderedImageTexture = 0;
  // ImGuiIO& io;
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
  void DrawVec3Controls(const char *, glm::vec3 &);
  void RenderImGUI();

  static void framebuffer_size_cb(GLFWwindow *, int, int);

public:
  AnglerED(uint16_t, uint16_t);
  ~AnglerED();

  void Loop();
};

