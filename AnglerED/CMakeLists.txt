project(AnglerED)

include_directories(
        "includes"
        "includes/imgui"
        "../external_includes"
        "../AnglerRT/includes/core"
        "../AnglerRT/includes/materials"
        "../AnglerRT/includes/shapes"
        "../AnglerRT/includes/image_formats"
        "../AnglerRT/includes"
	"../tools/tinyobjloader"
)

find_library(SPDLOG_LIB spdlog ../libs/spdlog)

SET(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/GLFW/)


add_executable(AnglerED
        src/main.cpp
        src/obj2angler.cpp
        src/glad.c
        src/imgui/imgui.cpp
        src/imgui/imgui_demo.cpp
        src/imgui/imgui_widgets.cpp
        src/imgui/imgui_draw.cpp
        src/imgui/imgui_impl_glfw.cpp
        src/imgui/imgui_impl_opengl3.cpp
        )

#target_link_libraries(AnglerED PRIVATE AnglerRT ${SPDLOG_LIB} glfw opengl32)
target_link_libraries(AnglerED PRIVATE AnglerRT spdlog glfw opengl32)
