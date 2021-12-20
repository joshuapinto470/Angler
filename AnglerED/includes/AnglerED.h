#pragma once

#ifdef __WIN32
#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

bool BindImageTexture(unsigned char *, GLuint *, int, int);
#endif

#include <algorithm>
#include <cstdio>
#include <thread>
#include <utility>

#include "AnglerRT.h"
#include "BVH.h"
#include "Render.h"

#include "obj2angler.h"

#include "scenes.h"