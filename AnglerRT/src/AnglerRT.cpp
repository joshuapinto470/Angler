#include "spdlog/spdlog.h"
#include "AnglerRT.h"

Color Trace(const Ray& ray, const Scene& scene, int max_depth)
{
    if(max_depth < 1)
        return {0, 0, 0};

    Interaction inter;

    if(scene.Hit(ray, 0.001, Infinity, inter)){
        Ray outRay;
        Color mColor;
        if(inter.material->BSDF(ray, mColor, inter, outRay)){
            // The material bounces light.
            return (mColor * Trace(outRay, scene, max_depth - 1));
        }
        return mColor;
    }
    return scene.GetEnvironmentTexture(ray);
}

void RenderScene(const Scene& scene, const Camera& camera, Options& options){
    
    options.isRenderActive = true;
    options.progress = 0.0f;
    options.image = nullptr;

    int image_height = options.iHeight;
    int image_width = options.iWidth;
    int samples_per_pixel = options.samples_per_pixel;
    int max_depth = options.max_depth;  

    spdlog::info("Starting Render");

    std::shared_ptr<PNG> myImage = std :: make_shared<PNG>("Rendered.png", options.iWidth, options.iHeight);

    //PNG myImage("Rendered.png", options.iWidth, options.iHeight);
    Float im_width  = (Float) 1.0 / (image_width + 1);
    Float im_height = (Float) 1.0 / (image_height + 1);

    float img_height = (float) 1.0 / image_height;

    for(int j = image_height - 1; j >= 0; --j)
    {
        options.progress = (float) (image_height - j) * img_height;// / image_height;
        for(int i = 0; i < image_width; ++i)
        {
            Color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) * im_width; // / (image_width - 1);
                auto v = (j + random_double()) * im_height;   // / (image_height - 1);

                Ray ray =  camera.get_ray(u, v);
                pixel_color = pixel_color +  Trace(ray, scene, max_depth);
            }
            pixel_color = pixel_color / samples_per_pixel;
            //camera.getFlim()->Write(pixel_color);
            myImage->Write(pixel_color);
        }
    }

    //camera->flushFlim();
    spdlog::info("Render Done!");
    options.image = myImage;
    options.isRenderActive = false;
}

/*
int main(){

    // Define the camera
    Camera camera(cameraFOV, aspect_ratio, Point(0, 0, 1.4), Point(0, 0, -1), Vec3f(0, 1, 0));

    // Define a scene.
    // This will hold all the world objects. like shapes, lights environment maps etc..
    Scene world;

    // Define the materials to use for the scene.
    std :: shared_ptr<Material> material1 = std :: make_shared<Lambertian>(Color(0.8, 0.1, 0.1));
    std :: shared_ptr<Material> material2 = std :: make_shared<Metallic>(Color(0.9, 0.9, 0.9), 0.05);
    std :: shared_ptr<Material> material3 = std :: make_shared<Emissive>(Color(1.0, 1.0, 1.0), 1);
    std :: shared_ptr<Material> glass_mat = std :: make_shared<Glass>(Color(1.0, 1.0, 1.0), 1.0, 1.0);

    // Add the objects to the scene.
    // objects should be created as shared pointers.
    world.Add( std :: make_shared<Sphere>(Point(0, 0, -1), 0.5, material1));
    world.Add( std :: make_shared<Sphere>(Point(-2, 0, -1), 0.5, glass_mat));
    world.Add( std :: make_shared<Sphere>(Point(2, 0, -1), 0.5, material3));

    // Environment map (optional).
    // by default it will use a interpolated value.
    std :: shared_ptr<EnvironmentTexture> envTex = std ::make_shared<EnvironmentTexture>(R"(D:\Documents\C++\Old Projects\AnglerRT\round_platform_2k.png)");
    world.SetEnvironmentTexture(envTex);

    // finally render the scene.
    RenderScene(world, camera, options);

    return 0;
}
*/

class Render{
public:
    Color Trace();
};