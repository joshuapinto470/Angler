#include <Application.h>

#include <SceneManager.h>

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

    SceneManager::SceneManager* manager = new SceneManager::SceneManager();
    manager->Add(mModel, nullptr);

    UIEngine::ViewportWidget viewport = UIEngine::ViewportWidget("Viewport");
    viewport.SetScene(manager);

    UIEngine::WInfo demo = UIEngine::WInfo("Demo");
    UIEngine::WSceneViewer viewer = UIEngine::WSceneViewer("Scene hierarchy");
    viewer.SetScene(manager);

    UIEngine::WSettings setting = UIEngine::WSettings("Inspector");
    setting.SetScene(manager);

    Shader shader("/home/joshua/Projects/Angler/AnglerED/shaders/base.vert", "/home/joshua/Projects/Angler/AnglerED/shaders/base.frag");
    shader.use();

    glm::mat4 model = glm::mat4(1.0f);

    // Camera
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    /* Lighting info */
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.setVec3("lightPos", lightPos);

    while (!window.CloseWindow())
    {
        model = glm::rotate(model, glm::radians(0.15f), glm::vec3(0.f, 1.f, 0.f));
        shader.setMat4("model", model);
        engine.PreFrame();
        // Render stuff here.

        ui.StartUI();
        // Render widgets
        viewport.Render();
        demo.Render();
        viewer.Render();
        setting.Render();

        ui.EndUI();
        window.PrepareNextFrame();
    }
}
