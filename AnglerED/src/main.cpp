#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <thread>
#include <utility>
#include <algorithm>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "AnglerRT.h"
#include "Lambertian.h"

#include "obj2angler.h"

// TODO: Implement a GUI for anglerRT

Scene random_scene() {
    Scene world;

    auto ground_material = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Vec3f(0,-1000,0), 1000, ground_material));

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
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Vec3f(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(Vec3f (-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metallic>(Color(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(Vec3f(4, 1, 0), 1.0, material3));

    return world;
}

Scene MeshScene(){
    Scene world;

    std::vector<std::vector<std::shared_ptr<Shape>>> mesh = LoadMeshFromFile();

    // std :: shared_ptr<Material> material1 = std :: make_shared<Dielectric>(1.0);
    // std :: shared_ptr<Material> material3 = std :: make_shared<Metallic>(Color(0.8, 0.8, 0.5), 0.01);
    // std :: shared_ptr<Material> glass_mat = std :: make_shared<Glass>(Color(1.0, 1.0, 1.0), 1.0, 1.0);


    // world.Add( std :: make_shared<Sphere>(Point(0, 0, -1), 0.5, material1));
    // world.Add( std :: make_shared<Sphere>(Point(-2, 0, -1), 0.5, glass_mat));
    // world.Add( std :: make_shared<Sphere>(Point(2, 0, -1), 0.5, material3));

    for (auto& i : mesh){
        for(auto& j : i)
            world.Add(j);
    }
    return world;
}

Scene QuickScene(){
    Scene world;
    
    std :: shared_ptr<Material> material1 = std :: make_shared<Dielectric>(1.0);
    std :: shared_ptr<Material> material3 = std :: make_shared<Metallic>(Color(0.8, 0.8, 0.5), 0.01);
    std :: shared_ptr<Material> glass_mat = std :: make_shared<Glass>(Color(1.0, 1.0, 1.0), 1.0, 1.0);


    world.Add( std :: make_shared<Sphere>(Point(0, 0, -1), 0.5, material1));
    world.Add( std :: make_shared<Sphere>(Point(-2, 0, -1), 0.5, glass_mat));
    world.Add( std :: make_shared<Sphere>(Point(2, 0, -1), 0.5, material3));

    return world;
}

bool BindImageTexture(unsigned char* buffer, GLuint* out_texture, int image_width, int image_height)
{

    // Load from buffer
    unsigned char* image_data = buffer;
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    *out_texture = image_texture;

    return true;
}

int main()
{

    #ifndef NDEBUG
        spdlog::info("DEBUG BUILD");
        spdlog::info(__TIMESTAMP__);
    #endif

    spdlog::info("CPU Arch : {} bit", sizeof(void*) * 8);

    // AnglerRT initialization.
    float aspect_ratio = 16.0 / 9.0;

    Options options{};
    options.MAX_DEPTH = 4;
    options.SAMPLES_PER_PIXEL = 60;
    options.WIDTH = 512;
    options.HEIGHT = static_cast<int>(options.WIDTH / aspect_ratio);
    options.image = nullptr;

    int cameraFOV = 35.0;

    //Camera camera(cameraFOV, aspect_ratio, Point(14, 2, 3), Point(0, 0, 0), Vec3f(0, 1, 0));
    Camera camera(cameraFOV, aspect_ratio, Point(0, 0, 3), Point(0, 0, 0), Vec3f(0, 1, 0));

    Scene world = QuickScene();


    std :: shared_ptr<EnvironmentTexture> envTex = std :: make_shared<EnvironmentTexture>(R"(D:\Documents\C++\Old Projects\Angler\Textures\round_platform_2k.png)");
    world.SetEnvironmentTexture(envTex);

    // when isRenderActive is set to true the renderer is active.
    // Dont start another render process until the current one is finished or stopped.
    options.isRenderActive = false;

    //RenderScene(world, camera, options);

    GLFWwindow* window;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    int display_width = 1280, display_height = 720;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(display_width, display_height, "AnglerED", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    bool err = gladLoadGL() == 0;
    if(err){
        spdlog::error("OpenGL Error!");
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool show_demo_window = true;
    bool needToBindTexture = false;

    GLuint renderedImageTexture = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // #ifndef NDEBUG
        // ImGui::ShowDemoWindow(&show_demo_window);
        // #endif
        
        // Dont modify renderer setting while the renderer is active.
        if(!options.isRenderActive)
        {    
            ImGui::Begin("Renderer settings");
            ImGui::Text("AnglerRT Settings");
            ImGui::InputInt("Max Depth", &options.MAX_DEPTH);
            ImGui::InputInt("Samples", &options.SAMPLES_PER_PIXEL);
            ImGui::InputFloat("Aspect Ratio ", &aspect_ratio);
            ImGui::InputInt("Image Width", &options.WIDTH);
            options.HEIGHT = static_cast<int>(options.WIDTH / aspect_ratio);
            ImGui::Text("Resolution (%d X %d)", options.WIDTH, options.HEIGHT);
            ImGui::Separator();
            ImGui::Text("Camera Settings");
            ImGui::InputInt("Camera FOV", &cameraFOV);
            static float p[4] = { 0.f, 0.f, 3.f, 0.44f };
            static float q[4] = { 0.0f, 0.0f, 0.0f, 0.44f };
            if(ImGui::InputFloat3("Look From", p) ||
            ImGui::InputFloat3("Look At", q))
                camera = Camera(cameraFOV, aspect_ratio, Point(p[0], p[1], p[2]), Point(q[0], q[1], q[2]), Vec3f(0, 1, 0));
            ImGui::End();
        }

        {
            ImGui::Begin("Scene Builder");
            ImGui::Text("Build a scene to render.");
            ImGui::End();
        }

        {
            ImGui::Begin("AnglerRT");
            ImGui::Text("Render Window");
            
            if(ImGui::Button("Render Image") && !options.isRenderActive) {
                options.image = nullptr;
                std::thread render(RenderScene, std::ref(world), std::ref(camera), std::ref(options));
                render.detach();
                needToBindTexture = true;
            }
            else{
                ImGui::Text("Progress : %.2f %", options.progress * 100);
            }
            ImGui::End();
        }

        if(!options.isRenderActive && options.image){            
            if(needToBindTexture){
                spdlog::info("AnglerED : Binding texture data");
                //options.image->GammaCorrect();
                unsigned char* buffer = options.image->getBuffer().data();
                if(!BindImageTexture(buffer, &renderedImageTexture, options.WIDTH, options.HEIGHT))
                    spdlog::warn("AnglerED : Binding texture failed");
                needToBindTexture = false;
            }

            ImGui::Begin("Rendered Image");
            ImGui::Text("Image Size = %d x %d",
                        std::min(options.WIDTH, display_width - 100), 
                        std::min(options.HEIGHT, display_height - 100));

            ImGui::Image((void*)(intptr_t)renderedImageTexture, ImVec2(options.WIDTH, options.HEIGHT));
            ImGui::End();
            
        }
        ImGui::Render();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}