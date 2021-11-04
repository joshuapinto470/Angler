#pragma once

// Core
#include "Bounds.h"
#include "Camera.h"
#include "EnvironmentMap.h"
#include "Material.h"
#include "Random.h"
#include "Ray.h"
#include "Scene.h"
#include "Shape.h"
#include "Utilities.h"

// Materials
#include "Dielectric.h"
#include "Emissive.h"
#include "Glass.h"
#include "Lambertian.h"
#include "Metallic.h"

#include "PNG.h"
#include "PPM.h"

#include "Probe.h"

struct Options {
    Options() = default;

    int WIDTH, HEIGHT;
    int SAMPLES_PER_PIXEL;
    int MAX_DEPTH;
    // stats
    float progress;
    bool isRenderActive;

    std::shared_ptr<Image> image;
};
