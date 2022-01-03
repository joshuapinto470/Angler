project(AnglerED)
set (CMAKE_CXX_STANDARD 17)

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
        "includes"
)


find_library(SPDLOG_LIB spdlog ../libs/spdlog)
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(vendor/GLFW/)

SET(SRC_FILES 
src/main.cpp
src/scenes.cpp
src/obj2angler.cpp
src/glad.c
src/imgui/imgui.cpp
src/imgui/imgui_demo.cpp
src/imgui/imgui_widgets.cpp
src/imgui/imgui_draw.cpp
src/imgui/imgui_impl_glfw.cpp
src/imgui/imgui_impl_opengl3.cpp
)

add_executable(AnglerED
${SRC_FILES}
)

if(WIN32)
        target_link_libraries(AnglerED PRIVATE AnglerRT spdlog glfw opengl32)
endif(WIN32)

if(UNIX)
        target_link_libraries(AnglerED PRIVATE AnglerRT spdlog glfw GL)
endif(UNIX)
