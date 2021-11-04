#include "Render.h"

Render::Render(const Scene &scene, const Camera &camera, Options &options) {
    mScene = std::make_shared<Scene>(scene);
    mCamera = std::make_shared<Camera>(camera);
    mOptions = &options;

    auto nThreads = std::thread::hardware_concurrency();
    nThreads = (nThreads == 0) ? 1 : nThreads;
    spdlog::info("Detected {} threads", nThreads);

    options.isRenderActive = false;
    options.progress = 0.0f;
    options.image = nullptr;

    WIDTH = options.WIDTH;
    HEIGHT = options.HEIGHT;
    samples_per_pixel = options.SAMPLES_PER_PIXEL;
    max_depth = options.MAX_DEPTH;

    width_inv = (Float)1.0 / (WIDTH - 1);
    height_inv = (Float)1.0 / (HEIGHT - 1);
    samples_inv = (Float)1.0 / samples_per_pixel;

    mBuffer = std::make_shared<ImageBuffer>(WIDTH, HEIGHT);
}

void Render::StartRender() {
    // TODO: Implement multi-threading support here.
    // spawn multiple RenderScene instances with their own image buffers.
    // combine the image buffers and set the Options.image attribute to the buffer.

    // TODO: Implement tile based multithreading.
    // TODO: Implement progressive multithreading.

    mOptions->isRenderActive = true;

    spdlog::info("Starting Render");
    RenderScene();
    // PNG tImage(*mBuffer);
    spdlog::info("Render Done!");
    mOptions->image = mBuffer;
    mOptions->isRenderActive = false;
}

void Render::RenderScene() {

    for (int j = HEIGHT - 1; j >= 0; --j) {
        mOptions->progress = (float)(HEIGHT - j) * height_inv;

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
    mOptions->image = mBuffer;
}

Color Render::Trace(const Ray &ray, int max_depth) {
    if (max_depth < 1)
        return { 0, 0, 0 };

    Interaction inter;

    if (mScene->Hit(ray, 0.001, Infinity, inter)) {
        Ray outRay;
        Color mColor;
        if (inter.material->BSDF(ray, mColor, inter, outRay)) {
            return (mColor * Trace(outRay, max_depth - 1));
        }
        return mColor;
    }
    return mScene->GetEnvironmentTexture(ray);
}