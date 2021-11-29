#pragma once

#include <thread>

#include "AnglerRT.h"
#include "ImageBuffer.h"
#include "spdlog/spdlog.h"

struct Tile {
    Point2 start;
    Point2 end;
};

class Render {
  public:
    Render() = default;
    Render(const Scene &, const Camera &, Options &);
    void StartRender();

  private:
    void RenderScene();
    void InitFromOptions();
    Color Trace(const Ray &, int);

    std::shared_ptr<ImageBuffer> mBuffer;
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Scene> mScene;

    int WIDTH, HEIGHT;
    int nThreads;
    int samples_per_pixel, max_depth;

    Float width_inv, height_inv, samples_inv;

    Options *mOptions;
};

class Integrator {
  public:
    Integrator();
    Integrator(Tile);
    ~Integrator();

    void RenderTile();

  private:
    Color Trace(const Ray &, int);
    Tile tile;
    ImageBuffer buffer;
};
