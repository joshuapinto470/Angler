project(AnglerED)
set (CMAKE_CXX_STANDARD 17)

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_LEVEL 0)

# Detect current OS.
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Configuring for Windows")
    set(Angler_WINDOWS True)
#     SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup ")
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Configuring for MacOS")
    set(Angler_MACOS True)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Configuring for Linux")
    set(Angler_LINUX True)
endif ()


set(USE_AnglerRT False)

# Add local repository for FindXXX.cmake modules.
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/AnglerED/vendor/" ${CMAKE_MODULE_PATH})

include_directories(
        "includes/external/imgui"
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
        "includes/external"
        "includes/Renderer"
        "includes/WindowManager"
        "includes/Widgets"
        "includes/SceneManager"
        "includes/Utils"
        "includes/Entity"
)

find_library(SPDLOG_LIB spdlog ../libs/spdlog)
find_package(Assimp REQUIRED)
if(ASSIMP_FOUND)
message(STATUS "Assimp Found")
set(USE_ASSIMP True)
endif()

SET(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(${ASSIMP_INCLUDE_DIRS})
add_subdirectory(vendor/GLFW/)
add_subdirectory(vendor/EnTT/)

SET(SRC_FILES 
src/main.cpp
src/glad.c
src/AnglerED.cpp
src/Widgets/Widgets.cpp
src/Application.cpp
src/SceneManager/ModelLoader.cpp
src/SceneManager/SceneManager.cpp
src/SceneManager/ResourceManager.cpp
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

set(AnglerLibs spdlog glfw EnTT)

if(WIN32)
        set(AnglerLibs ${AnglerLibs} opengl32)
endif(WIN32)

if(UNIX)
        set(AnglerLibs ${AnglerLibs} GL)
endif(UNIX)

if(USE_ASSIMP)
        set(AnglerLibs ${AnglerLibs} ${ASSIMP_LIBRARIES})
        add_compile_definitions(USE_ASSIMP)
endif(USE_ASSIMP)

if(USE_AnglerRT)
        set(AnglerLibs ${AnglerLibs} AnglerRT)
endif(USE_AnglerRT)

target_link_libraries(AnglerED PRIVATE ${AnglerLibs})