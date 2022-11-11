#pragma once

#include <thread>

#include "AnglerRT.h"
#include "ImageBuffer.h"
#include "spdlog/spdlog.h"

class Render {
  public:
    Render() = delete;
    Render(const Scene &, const Camera &, Options &);
    void StartRender();

  private:
    void RenderScene(int);
    void InitFromOptions();
    Color Trace(const Ray &, int);

    std::shared_ptr<ImageBuffer> mBuffer;
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Scene> mScene;

    int WIDTH{}, HEIGHT{};
    unsigned int nThreads{};
    int SamplesPerPixel{}, MaxDepth{};

    Float width_inv{}, height_inv{}, samples_inv{};
    int rayCasts{};
    int envRays{};

    Ray outRay;
    Color mColor;
    Interaction inter;

    Options *mOptions{};
};