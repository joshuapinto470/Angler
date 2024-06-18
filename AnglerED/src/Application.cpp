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
    GLEngine::GLEngine::Init();
}

void App::Loop()
{
    AssimpLoader loader;
    Model mModel = loader.LoadModel("/home/joshua/Projects/Angler/res/models/Basic gltf/basic.glb");
    // Model mModel2 = loader.LoadModel("/home/joshua/3DModels/external/glTF-Sample-Assets/Models/Sponza/glTF/Sponza.gltf");

    auto *manager = new SceneManager::SceneManager();
    manager->Add(mModel, nullptr);
    // manager->Add(mModel2, nullptr);

    UIEngine::ViewportWidget viewport = UIEngine::ViewportWidget( "Viewport");
    viewport.SetScene(manager);

    UIEngine::WInfo demo = UIEngine::WInfo("Demo");
    UIEngine::WSceneViewer viewer = UIEngine::WSceneViewer("Scene hierarchy");
    viewer.SetScene(manager);

    UIEngine::WSettings setting = UIEngine::WSettings("Inspector");
    setting.SetScene(manager);

    Shader defaultShader = manager->getDefaultShader();

    defaultShader.use();

    auto model = glm::mat4(1.0f);

    // Camera
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 2.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    defaultShader.setMat4("view", view);
    defaultShader.setMat4("projection", projection);

    /* Lighting info */
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    defaultShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    defaultShader.setVec3("lightPos", lightPos);

    float ar = 16.0f / 9.0f;
    while (!window.CloseWindow())
    {
        model = glm::rotate(model, glm::radians(0.15f), glm::vec3(0.f, 1.f, 0.f));
        glm::vec2 viewportDim = viewport.getViewportDim();
        defaultShader.setMat4("model", model);

        if (viewportDim.y > 0.0001)
        {
            ar = viewportDim.x / viewportDim.y;
        }

        projection = glm::perspective(glm::radians(45.0f), ar, 0.1f, 100.0f);
        defaultShader.setMat4("projection", projection);

        GLEngine::GLEngine::PreFrame();
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

    // Put this in the destructor.
    delete manager;
}
