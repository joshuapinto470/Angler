#include "Render.h"
#include <chrono>

Render::Render(const Scene &scene, const Camera &camera, Options &options) {
    mScene = std::make_shared<Scene>(scene);
    mCamera = std::make_shared<Camera>(camera);
    mOptions = &options;

    auto nThreads = std::thread::hardware_concurrency();
    nThreads = (nThreads == 0) ? 1 : nThreads;
    spdlog::info("Detected {} threads", nThreads);

    InitFromOptions();
}

/*
    Initialize the renderer with the options selected
    by the user every time we render the scene.
*/
void Render::InitFromOptions() {
    mOptions->isRenderActive = false;
    mOptions->progress = 0.0f;
    mOptions->image = nullptr;

    WIDTH = mOptions->WIDTH;
    HEIGHT = mOptions->HEIGHT;
    samples_per_pixel = mOptions->SAMPLES_PER_PIXEL;
    max_depth = mOptions->MAX_DEPTH;

    width_inv = (Float)1.0 / (WIDTH - 1);
    height_inv = (Float)1.0 / (HEIGHT - 1);
    samples_inv = (Float)1.0 / samples_per_pixel;
    mBuffer = nullptr;

    rayCasts = 0;
    envRays = 0;
}

void Render::StartRender() {
    std ::chrono ::time_point<std::chrono::high_resolution_clock> wallStart, wallEnd;
    std ::chrono ::time_point<std::chrono::high_resolution_clock> renderStart, renderEnd;
    spdlog::info("Samples per pixel : {}", samples_per_pixel);
    spdlog::info("Starting Render");

    wallStart = std::chrono::high_resolution_clock::now();

    InitFromOptions();
    mOptions->isRenderActive = true;

    mBuffer = std::make_shared<ImageBuffer>(WIDTH, HEIGHT);

    renderStart = std::chrono::high_resolution_clock::now();
    RenderScene();
    renderEnd = std::chrono::high_resolution_clock::now();

    PNG tImage(*mBuffer);

    mOptions->image = mBuffer;

    wallEnd = std::chrono::high_resolution_clock::now();
    spdlog::info("Render Done!");

    std::chrono::duration<double> elapsedRender = renderEnd - renderStart;
    std::chrono::duration<double> elapsedWall = wallEnd - wallStart;

    spdlog::info("Total ray casts : {} rays", rayCasts);
    spdlog::info("Total environment rays : {} rays", envRays);
    spdlog::info("Percent of environment rays : {} %", ((float)envRays / rayCasts) * 100.0f);
    spdlog::info("Render Time : {} seconds", elapsedRender.count());
    spdlog::info("Wall Time : {} seconds", elapsedWall.count());
    spdlog::info("Render to Wall delta : {} ", elapsedWall.count() - elapsedRender.count());

    mOptions->isRenderActive = false;
}

void Render::RenderScene() {
    float h_inv = 1.0 / HEIGHT;

    for (int j = HEIGHT - 1; j >= 0; --j) {
        mOptions->progress = (float)(HEIGHT - j) * h_inv;

        for (int i = 0; i < WIDTH; ++i) {
            Color pixel_color(0, 0, 0);

            for (int s = 0; s < samples_per_pixel; ++s) {
                Float u = (i + random_double()) * width_inv;
                Float v = (j + random_double()) * height_inv;

                Ray ray = mCamera->get_ray(u, v);
                pixel_color = pixel_color + Trace(ray, max_depth);
            }

            pixel_color = pixel_color * samples_inv;
            mBuffer->Write(pixel_color);
        }
    }
}

void Integrator::RenderTile() {
}

Color Render::Trace(const Ray &ray, int max_depth) {
    if (max_depth < 1)
        return { 0, 0, 0 };

    rayCasts++;

    // Interaction inter;

    if (mScene->Hit(ray, 0.001, Infinity, inter)) {
        // Ray outRay;
        // Color mColor;
        if (inter.material->BSDF(ray, mColor, inter, outRay)) {
            return (mColor * Trace(outRay, max_depth - 1));
        }
        return mColor;
    }
    envRays++;
    return mScene->GetEnvironmentTexture(ray);
}