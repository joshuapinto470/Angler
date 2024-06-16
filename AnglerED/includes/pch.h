/* Pre compiled headers */
#pragma once

// External libs
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glm/gtc/matrix_transform.hpp>

#include "spdlog/spdlog.h"

// Standard libs
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <thread>
#include <memory>
#include <utility>

#include <EDBenchmark.h>

typedef glm::vec<2, unsigned> vec2u;
typedef glm::vec2 vec2f;