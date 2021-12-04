#include "scenes.h"

Scene random_scene() {
    Scene world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Vec3f(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Vec3f center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - Vec3f(4, 0.2, 0)).Length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_color() * random_color();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_color();
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metallic>(albedo, fuzz);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(0.7);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Vec3f(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(Vec3f(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metallic>(Color(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(Vec3f(4, 1, 0), 1.0, material3));

    // return world;
    return Scene(std::make_shared<BVH>(world, 0.0, 1.0));
}

Scene MeshScene() {
    Scene world;

    std::vector<std::vector<std::shared_ptr<Shape>>> mesh = LoadMeshFromFile();

    // std :: shared_ptr<Material> material1 = std :: make_shared<Dielectric>(1.0);
    // std :: shared_ptr<Material> material3 = std :: make_shared<Metallic>(Color(0.8, 0.8, 0.5), 0.01);
    // std :: shared_ptr<Material> glass_mat = std :: make_shared<Glass>(Color(1.0, 1.0, 1.0), 1.0, 1.0);

    // world.Add( std :: make_shared<Sphere>(Point(0, 0, -1), 0.5, material1));
    // world.Add( std :: make_shared<Sphere>(Point(-2, 0, -1), 0.5, glass_mat));
    // world.Add( std :: make_shared<Sphere>(Point(2, 0, -1), 0.5, material3));

    for (auto &i : mesh) {
        for (auto &j : i)
            world.Add(j);
    }
    return world;
}

Scene QuickScene() {
    Scene world;

    std ::shared_ptr<Material> material1 = std ::make_shared<Dielectric>(1.0);
    std ::shared_ptr<Material> material3 = std ::make_shared<Metallic>(Color(0.8, 0.8, 0.5), 0.01);
    std ::shared_ptr<Material> glass_mat = std ::make_shared<Glass>(Color(1.0, 1.0, 1.0), 1.0, 1.0);

    world.Add(std ::make_shared<Sphere>(Point(0, 0, -1), 0.5, material1));
    world.Add(std ::make_shared<Sphere>(Point(-2, 0, -1), 0.5, glass_mat));
    world.Add(std ::make_shared<Sphere>(Point(2, 0, -1), 0.5, material3));

    return world;
}
