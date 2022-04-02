#include "AnglerED.h"

class AnglerED {
  private:
    // Display settings
    GLFWwindow *window;
    GLuint renderedImageTexture = 0;
    uint16_t HEIGHT, WIDTH;
    bool needToBindTexture;

    // Renderer settings
    Render *mRenderer;
    Camera &mCamera;
    Options &options;
    //ImGuiIO &io;
    int cameraFOV;
    float aspect_ratio;
    // ImGUI

    void Init();
    void DrawRenderWindow();
    void DrawSceneMenu();
    void DrawSettingsMenu();
    void DrawRenderButton();
    void DrawScenePicker();

  public:
    AnglerED(uint16_t, uint16_t, Render *, Camera &, Options &, GLFWwindow* );
    ~AnglerED();

    void Loop();
};

AnglerED ::AnglerED(uint16_t Width, uint16_t Height, Render *Renderer, Camera &camera, Options &opt, GLFWwindow* Window)
    :mCamera(camera), options(opt) {

    window = Window;
    WIDTH = Width;
    HEIGHT = Height;

    mRenderer = Renderer;
    mCamera = camera;

    cameraFOV = 35.0f;
    aspect_ratio = 16.0f / 9.0f;

    needToBindTexture = false;
}

AnglerED ::~AnglerED() {
    delete mRenderer;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

void AnglerED ::DrawSettingsMenu() {
    // The settings for the renderer.
    // This is disabled when the renderer is active
    ImGui::Begin("AnglerRT settings");
    if (!options.isRenderActive) {
        ImGui::Text("Renderer Settings");
        ImGui::InputInt("Max Depth", &options.MAX_DEPTH);
        ImGui::InputInt("Samples", &options.SAMPLES_PER_PIXEL);
        ImGui::InputFloat("Aspect Ratio ", &aspect_ratio);
        ImGui::InputInt("Image Width", &options.WIDTH);
        options.HEIGHT = static_cast<int>(options.WIDTH / aspect_ratio);
        ImGui::Text("Resolution (%d X %d)", options.WIDTH, options.HEIGHT);
        ImGui::Separator();
        ImGui::Text("Camera Settings");
        ImGui::InputInt("Camera FOV", &cameraFOV);
        static float p[4] = { 0.f, 3.f, 10.f, 0.44f };
        static float q[4] = { 0.0f, 0.0f, 0.0f, 0.44f };
        if (ImGui::InputFloat3("Look From", p) || ImGui::InputFloat3("Look At", q))
            mCamera = Camera(cameraFOV, aspect_ratio, Point(p[0], p[1], p[2]), Point(q[0], q[1], q[2]), Vec3f(0, 1, 0));
    } else {
        ImGui::Text("Render is in progress.");
    }
    ImGui::End();
}

void AnglerED ::DrawRenderButton() {
    // Spawn a render thread when the button is pressed.
    // If the renderer is active then display the progress of the renderer.
    ImGui::Begin("AnglerRT");
    ImGui::Text("Render Window");

    if (ImGui::Button("Render Image") && !options.isRenderActive) {
        options.image = nullptr;

        std::thread render(&Render::StartRender, *mRenderer);
        render.detach();

        // renderer.StartRender();
        needToBindTexture = true;
    } else {
        ImGui::Text("Progress : %.2f %%", options.progress * 100);
    }
    ImGui::End();
}

void AnglerED ::DrawSceneMenu() {
    ImGui::Begin("Scene Settings");
    ImGui::Text("Resolution (%d X %d)", options.WIDTH, options.HEIGHT);
    ImGui::Text("Max Depth: %d", options.MAX_DEPTH);
    ImGui::Text("Samples: %d", options.SAMPLES_PER_PIXEL);
    ImGui::Text("Aspect Ratio: %.2f", aspect_ratio);
    ImGui::Separator();
    ImGui::Text("Camera FOV: %d", cameraFOV);
    ImGui::End();
}

void AnglerED ::DrawScenePicker() {
    ImGui::Begin("Scene Picker");
    const char *items[] = { "Random Scene", "Mesh Scene", "Sphere Scene", "Quick Scene" };
    static int item_current_idx = 0;
    const char *combo_label = items[item_current_idx];

    if (ImGui::BeginCombo("Scene", combo_label)) {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++) {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected))
                item_current_idx = n;

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
                ImGui::SetItemDefaultFocus();

            switch (item_current_idx) {
            case 0:
                spdlog::info("Selected scene 1");
                break;
            case 1:
                spdlog::info("Selected scene 2");
                break;
            default:
                break;
            }
        }
        ImGui::EndCombo();
    }
    ImGui::End();
}

void AnglerED ::DrawRenderWindow() {
    // Check if the renderer is inactive and there is
    // an image to display
    if (!options.isRenderActive && options.image) {
        // Check if need to bind the texture to OpenGL.
        // This is done once when we get a new image from the renderer.
        if (needToBindTexture) {
            // Bind the texture to OpenGL.
            spdlog::info("AnglerED : Binding texture data");

            std::shared_ptr<uint8_t[]> mBuffer = options.image->getBufferCopy();
            int BufferSize = options.HEIGHT * options.WIDTH * 4;
            auto *buffer = new unsigned char[BufferSize];
            memcpy(buffer, mBuffer.get(), BufferSize);

            if (!BindImageTexture(buffer, &renderedImageTexture, options.WIDTH, options.HEIGHT))
                spdlog::warn("AnglerED : Binding texture failed");
            needToBindTexture = false;
            delete[] buffer;
        }

        // Display the rendered image
        ImGui::Begin("Rendered Image");
        ImGui::Text("Image Size = %d x %d", std::min(options.WIDTH, (int)WIDTH), std::min(options.HEIGHT, (int)HEIGHT));

        ImGui::Image((void *)(intptr_t)renderedImageTexture, ImVec2(options.WIDTH, options.HEIGHT));
        ImGui::End();
    }
}

void AnglerED ::Loop() {

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        DrawScenePicker();

        DrawSettingsMenu();
        DrawSceneMenu();
        DrawRenderButton();
        DrawRenderWindow();

        ImGui::Render();

        glClearColor(0.117f, 0.117f, 0.117f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

int main(int argc, char *argv[]) {

    spdlog::info("CPU Arch : {} bit", sizeof(void *) * 8);

    // AnglerRT initialization.
    float aspect_ratio = 16.0 / 9.0;

    Options options;
    options.MAX_DEPTH = 4;
    options.SAMPLES_PER_PIXEL = 60;
    options.WIDTH = 512;
    options.HEIGHT = static_cast<int>(options.WIDTH / aspect_ratio);
    options.image = nullptr;

    int cameraFOV = 35;

    // Camera camera(cameraFOV, aspect_ratio, Point(14, 2, 3), Point(0, 0, 0), Vec3f(0, 1, 0));
    Camera camera = Camera(cameraFOV, aspect_ratio, Point(0, 1, 10), Point(0, 0, 0), Vec3f(0, 1, 0));

    Scene world = SphereScene();

    const char *TextureFilePath = "D:/Documents/C++/Angler/Angler_ED_RT/Angler/Textures/UV_Debug.png";

    std ::shared_ptr<EnvironmentTexture> envTex = std ::make_shared<EnvironmentTexture>(TextureFilePath);
    world.SetEnvironmentTexture(nullptr);
    options.isRenderActive = false;

    Render *renderer = new Render(world, camera, options);

    GLFWwindow *window;
    ImGuiIO& io = ImGui::GetIO();
    //(void)io;

    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    if (!glfwInit()) {
        spdlog::error("OpenGL Error! (GLFW INIT FAILED!)");
        return -1;
    }

    int WIDTH = 1024;
    int HEIGHT = 600;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "AnglerED", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        spdlog::error("OpenGL Error! (WINDOW CREATION FAILED!)");
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    bool err = gladLoadGL() == 0;
    if (err) {
        spdlog::error("OpenGL Error!");
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    (void) io;
    
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    AnglerED anglerED(1024, 600, renderer, camera, options, window);
    anglerED.Loop();

    return 0;
}

bool BindImageTexture(unsigned char *buffer, GLuint *out_texture, int image_width, int image_height) {

    // Load from buffer
    unsigned char *image_data = buffer;
    if (image_data == nullptr)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    *out_texture = image_texture;

    return true;
}
