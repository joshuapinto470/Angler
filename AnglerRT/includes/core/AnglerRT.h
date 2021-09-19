#pragma once

//Core
#include "Camera.h"
#include "Scene.h"
#include "Ray.h"
#include "Shape.h"
#include "Utilities.h"
#include "Material.h"
#include "Random.h"
#include "EnvironmentMap.h"

// Materials
#include "Lambertian.h"
#include "Emissive.h"
#include "Metallic.h"
#include "Glass.h"
#include "Dielectric.h"

#include "PPM.h"
#include "PNG.h"

#include "Probe.h"

struct Options{
    Options() = default;
    
    int WIDTH, HEIGHT;
    int SAMPLES_PER_PIXEL;
    int MAX_DEPTH;
    // stats
    float progress;
    bool isRenderActive;

    std::shared_ptr<PNG> image;
};

Color Trace(const Ray&, const Scene&, int);
void RenderScene(const Scene&, const Camera&, Options&);