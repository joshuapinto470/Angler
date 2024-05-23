#include <Application.h>

App::App()
{
    engine = GLEngine::GLEngine();
    ui = UIEngine::UIEngine(true); // docking false
    window = jWindowManager::WindowManager();
}

App::~App()
{
    ui.UIShutdown();
}

void App::Init()
{
    window.Init(1280, 720, "AnglerED");
    ui.Init(window);
    engine.Init();
}

void App::Loop()
{
    ModelLoader loader;
    Model mModel = loader.LoadModel("/home/joshua/Projects/Angler/res/simple.obj");
    mModel.initModel();

    UIEngine::ViewportWidget wg = UIEngine::ViewportWidget("Viewport");
    UIEngine::WInfo demo = UIEngine::WInfo("Demo");

    Shader shader("/home/joshua/Projects/Angler/res/base.vert", "/home/joshua/Projects/Angler/res/base.frag");
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);

    // Camera
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    /* Lighting info */
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos", lightPos);

    while (!window.CloseWindow())
    {
        engine.PreFrame();
        // Render stuff here.
        mModel.Draw();

        ui.StartUI();
        // Render widgets
        wg.Render();
        demo.Render();
        ui.EndUI();
        window.PrepareNextFrame();
    }
}
