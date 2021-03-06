#include "RetEngine.h"
#include "retTime.h"
#include <glad/glad.h>
#include <iostream>

#include "Camera.h"
#include "Rendering/Shader.h"
#include "Component/Render.h"
#include "Component/Model.h"
#include "Component/CameraController.h"
#include "Component/Rigidbody.h"
#include "Physics/PhysicsEngine.h"
#include "Component/Collider.h"

ret::RetEngine* ret::RetEngine::instance = 0;

ret::RetEngine::RetEngine() : window_(std::unique_ptr<Window>())
{
}

ret::RetEngine::~RetEngine()
{
    delete physics;
    delete renderer;
}

int ret::RetEngine::Start()
{
    if (instance != nullptr)
        return -1;

    instance = new RetEngine();

    int e = instance->Run();

    delete instance;
    instance = nullptr;

    return e;
}

int ret::RetEngine::Run()
{
    window_ = std::unique_ptr<Window>(new Window(1280, 720, "Smile"));

    ret::Time::Start();
    physics = new PhysicsEngine();
    renderer = new Renderer();

    Entity* ePtr;

    {
        ret::Scene& scene1 = CreateScene();

        Material* mat = ret::MaterialManager::GetMaterial("Dank");
        {
            Texture* tex;
            // TEXTURE 1
            tex = ret::TextureManager::GetTexture("Assets/Textures/container2.png");
            tex->type = "diffuse";
            mat->textures.push_back(tex);
            // TEXTURE 2        
            tex = ret::TextureManager::GetTexture("Assets/Textures/container2_specular.png");
            tex->type = "specular";
            mat->textures.push_back(tex);
            // TEXTURE 3
            tex = ret::TextureManager::GetTexture("Assets/Textures/superjoy.png", 3);
            tex->type = "diffuse";
            mat->textures.push_back(tex);

            mat->shader = ret::ShaderManager::GetShader("test_shader");
        }

        Entity* tree = new Entity();
        ePtr = tree;
        tree->transform.position = glm::vec3(0, 0, 2);
        tree->transform.scale = glm::vec3(0.25f);
        Render* render = new ret::Render();
        render->model = ret::ModelManager::GetModel("Assets/Models/robo.fbx");
        render->mat = mat;
        render->layer = 0x01;
        tree->AddComponent(render);
        scene1.entities_.push_back(tree);

        Entity* box;
        for (uint32_t i = 0; i < 30; i++)
        {
            box = new Entity(); 
            box->transform.position = glm::vec3(i*0.25, i*10+40, -2);
            box->transform.scale = glm::vec3(1.0f);
            Render* render = new ret::Render();
            render->model = ret::ModelManager::GetModel("Assets/Models/robo.fbx");
            render->mat = mat;
            render->layer = 0x01;
            box->AddComponent(render);
            ret::Collider* col = new ret::Collider();
            col->setCube(0.5);
            RigidBody* rb = new RigidBody(col);
            box->AddComponent(rb);
            scene1.entities_.push_back(box);
        }

        Entity* cam = new Entity();
        cam->transform.position = glm::vec3(-4, -1, 0);
        Camera* camComponent = new Camera();
        renderer->camera = camComponent;
        CameraController* testComp = new CameraController();
        cam->AddComponent(camComponent);
        cam->AddComponent(testComp);
        scene1.entities_.push_back(cam);

        std::cout << tree->id << " " << box->id << " " << cam->id << std::endl;
    }

    fixedAccumulator = 0.0;
    accumulator = 0.0;
    double lastFrame = 0.0;

    while (window_->IsActive())
    {
        ret::Time::Update();

        accumulator += ret::Time::GetDeltaTime();
        fixedAccumulator += ret::Time::GetDeltaTime();

        std::cout << "FPS = " << 1 / ret::Time::GetDeltaTime() << std::endl;

        double stepSize = 1.0 / 60.0;
        if (fixedAccumulator > stepSize)
        {
            physics->Update();
            fixedAccumulator -= stepSize;
        }

        for (auto& scene : scenes_)
        {
            scene.UpdateEntities();
        }
        
        renderer->Draw();
        //debugRenderer->Draw();
    }

    return 0;
}

ret::Scene& ret::RetEngine::CreateScene()
{
    scenes_.push_back(ret::Scene());
    return scenes_.back();
}
