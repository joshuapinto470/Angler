project(AnglerED)
set (CMAKE_CXX_STANDARD 17)

# add_compile_definitions(USE_ASSIMP)

include_directories(
        "includes/imgui"
        "../external_includes"
        "../AnglerRT/includes/core"
        "../AnglerRT/includes/accelerators"
        "../AnglerRT/includes/materials"
        "../AnglerRT/includes/shapes"
        "../AnglerRT/includes/image_formats"
        "../AnglerRT/includes"
      	"../tools/tinyobjloader"
        "../tools/glm"
        "includes"
        "includes/Renderer"
        "includes/WindowManager"
        "includes/Widgets"
        "includes/SceneManager"
        "includes/Utils"
        "includes/Entity"
)

find_library(SPDLOG_LIB spdlog ../libs/spdlog)
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/GLFW/)
add_subdirectory(vendor/EnTT/)

SET(SRC_FILES 
src/main.cpp
src/glad.c
src/AnglerED.cpp
src/scenes.cpp
src/obj2angler.cpp
src/Widgets/Widgets.cpp
src/Application.cpp
src/SceneManager/ModelLoader.cpp
src/SceneManager/SceneManager.cpp
src/Entity/GLModel.cpp
src/Entity/GLMesh.cpp
src/Entity/GLCamera.cpp
src/Entity/GLLight.cpp
src/Entity/GLEntity.cpp
src/Renderer/Shader.cpp
src/Renderer/GLEngine.cpp
src/Renderer/Renderer.cpp
src/Renderer/UIEngine.cpp
src/Renderer/GLMaterial.cpp
src/WindowManager/WindowManager.cpp
src/imgui/imgui.cpp
src/imgui/imgui_demo.cpp
src/imgui/imgui_widgets.cpp
src/imgui/imgui_draw.cpp
src/imgui/imgui_impl_glfw.cpp
src/imgui/imgui_impl_opengl3.cpp
src/imgui/imgui_tables.cpp
)



add_executable(AnglerED
${SRC_FILES}
)

if(WIN32)
        target_link_libraries(AnglerED PRIVATE AnglerRT spdlog glfw opengl32 EnTT)
endif(WIN32)

if(UNIX)
        target_link_libraries(AnglerED PRIVATE AnglerRT spdlog glfw GL EnTT)
endif(UNIX)
