# USEAGE

```c++

int main() {

    // Vectors and math.
    // Define a 3d point with x, y, z coords as 1.0, 3.0, 5.0
    Point p(1.0, 3.0, 5.0);

    // Define the camera
    Camera camera(cameraFOV, aspect_ratio, <point_from>, <point_to>, <up_vector>);

    // Define a scene.
    // This will hold all the world objects. like shapes, lights, environment maps etc..
    Scene world;

    // Define the materials to use for the scene.
    std ::shared_ptr<Material> matL = std ::make_shared<Lambertian>(Color(0.8, 0.1, 0.1));
    std ::shared_ptr<Material> matM = std ::make_shared<Metallic>(Color(0.9, 0.9, 0.9), 0.05);
    std ::shared_ptr<Material> matE = std ::make_shared<Emissive>(Color(1.0, 1.0, 1.0), 1);
    std ::shared_ptr<Material> matG = std ::make_shared<Glass>(Color(1.0, 1.0, 1.0), 1.0, 1.0);

    // Add the objects to the scene.
    // objects should be created as shared pointers.
    world.Add(std ::make_shared<Sphere>(Point(0, 0, -1), 0.5, matL));
    world.Add(std ::make_shared<Sphere>(Point(-2, 0, -1), 0.5, matG));
    world.Add(std ::make_shared<Sphere>(Point(2, 0, -1), 0.5, matE));

    // Environment map (optional).
    // by default it will use a interpolated value.
    std ::shared_ptr<EnvironmentTexture> envTex = std ::make_shared<EnvironmentTexture>(R"(PATH)");
    world.SetEnvironmentTexture(envTex);

    // We need to set the options.
    Options options;
    options.MAX_DEPTH = 4;
    options.SAMPLES_PER_PIXEL = 60;
    options.WIDTH = 512;
    options.HEIGHT = static_cast<int>(options.WIDTH / aspect_ratio);
    options.image = nullptr;
    options.isRenderActive = false;

    // Finally to render the scene
    // Create a render object then call the StartRender method.
    Render render(world, camera, options);
    render.StartRender();

    return 0;
}
```