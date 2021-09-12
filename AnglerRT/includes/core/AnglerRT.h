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
    
    int iWidth, iHeight;
    int samples_per_pixel;
    int max_depth;
    // stats
    float progress;
    bool isRenderActive;

    std :: shared_ptr<PNG> image;
};

Color ray_color(const Ray&, const Scene&, int);
void RenderScene(const Scene&, const Camera&, Options&);