project(AnglerRT)

include_directories("includes"
                    "includes/accelerators"
                    "includes/core"
                    "includes/shapes"
                    "includes/materials"
                    "includes/image_formats"
                    )

find_library(SPDLOG_LIB spdlog ../libs/spdlog)

add_library(AnglerRT src/AnglerRT.cpp
        src/shapes/Sphere.cpp
        src/shapes/Triangle.cpp
        src/shapes/Plane.cpp
        src/materials/Lambertian.cpp
        src/materials/Emissive.cpp
        src/materials/Metallic.cpp
        src/materials/Dielectric.cpp
        src/materials/Glass.cpp
        src/external/lodepng.cpp
        src/image_formats/PPM.cpp
        src/image_formats/PNG.cpp
        src/core/Camera.cpp
        src/core/Texture.cpp
        src/core/EnvironmentMap.cpp
        src/core/Scene.cpp
        src/core/Probe.cpp
        src/accelerators/BVH.cpp
        )

target_link_libraries(AnglerRT PRIVATE spdlog)