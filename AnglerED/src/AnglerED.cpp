#include <AnglerED.h>

static void glfw_error_callback(int, const char*);

int AnglerED ::Init(){
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, "AnglerED", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    gladLoadGL();
    //glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    return 1;
}

AnglerED ::AnglerED(uint16_t Width, uint16_t Height){
    //Options options;
    aspect_ratio = 16.0f / 9.0f;
    cameraFOV = 35.0f;
    
    options.MAX_DEPTH = 4;
    options.SAMPLES_PER_PIXEL = 30;
    options.WIDTH = Width;
    options.HEIGHT = static_cast<int>(options.WIDTH / aspect_ratio);
    options.image = nullptr;

    WIDTH = options.WIDTH;
    HEIGHT = options.HEIGHT;



    // Camera camera(cameraFOV, aspect_ratio, Point(14, 2, 3), Point(0, 0, 0), Vec3f(0, 1, 0));
    mCamera = Camera(cameraFOV, aspect_ratio, Point(0, 1, 10), Point(0, 0, 0), Vec3f(0, 1, 0));

    //mWorld = SphereScene();
    //mWorld = MeshScene();
    //mWorld = QuickScene();
    mWorld = RandomScene();

    //const char *TextureFilePath = "E:/Documents/C++/Angler/Angler/build/Textures/UV_Debug.png";

    //std ::shared_ptr<EnvironmentTexture> envTex = std ::make_shared<EnvironmentTexture>(TextureFilePath);
    mWorld.SetEnvironmentTexture(nullptr);
    options.isRenderActive = false;

    mRenderer = new Render(mWorld, mCamera, options);
    
    Init();
}

AnglerED ::~AnglerED() {
    delete mRenderer;

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
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
        lastPassIndex = 1;
        delete mRenderer;
        mRenderer = new Render(mWorld, mCamera, options);
        std::thread render(&Render::StartRender, *mRenderer);
        render.detach();

        // renderer.StartRender();
        needToBindTexture = true;
    } else {
        ImGui::Text("Progress : %.2f %%", options.progress * 100);
        ImGui::Text("Pass : %d / %d", options.pass, options.SAMPLES_PER_PIXEL);
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
                //spdlog::info("Selected scene 1");
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
    if (options.image) {
        if(options.pass - lastPassIndex > 2){
                lastPassIndex = options.pass;
                std::shared_ptr<float[]> mBuffer = options.image->getBufferCopy();
                int BufferSize = options.HEIGHT * options.WIDTH * 4;
                auto *buffer = new float[BufferSize];
                memcpy(buffer, mBuffer.get(), BufferSize * sizeof(float));

                if (!BindImageTexture(buffer, &renderedImageTexture, options.WIDTH, options.HEIGHT))
                    spdlog::warn("AnglerED : Binding texture failed");
                needToBindTexture = false;
                delete[] buffer;
        }
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
        DrawScenePicker();
        DrawRenderButton();
        DrawRenderWindow();

        ImGui::Render();
        glfwGetFramebufferSize(window, &WIDTH, &HEIGHT);
        glViewport(0, 0, WIDTH, HEIGHT);
        glClearColor(0.117f, 0.117f, 0.117f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

    }
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}



bool BindImageTexture(float *buffer, GLuint *out_texture, int image_width, int image_height) {

    // Load from buffer
    float *image_data = buffer;
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_FLOAT, image_data);

    *out_texture = image_texture;

    return true;
}

