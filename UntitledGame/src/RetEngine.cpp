#include "RetEngine.h"
#include "retTime.h"
#include <glad/glad.h>
#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "Managers/ShaderManager.h"
#include "Component/Model.h"

ret::RetEngine::RetEngine() : window_(NULL)
{
}

ret::RetEngine::~RetEngine()
{
}

int ret::RetEngine::Run()
{
    window_ = new Window(1280, 720, "Smile");

    ret::Time::Start();

    ret::Scene scene1;

    Entity tree;
    tree.transform.position = glm::vec3(0, 1, 2);
    tree.transform.scale = glm::vec3(0.1f);
    Model fatTree("Assets/Models/fattree.obj");
    renderer.AddModel(&fatTree);
    tree.AddComponent(&fatTree);
    scene1.entities_.push_back(tree);

    Entity box;
    Model cube;
    renderer.AddModel(&cube);
    box.AddComponent(&cube);
    scene1.entities_.push_back(box);

    Entity cam;
    ret::Camera camera;
    cam.AddComponent(&camera);
    renderer.camera = &camera;
    scene1.entities_.push_back(cam);

    auto camComp = cam.GetComponent<ret::Model>();

    scene1.Save("Assets/Scenes/scene3.rsc");
    scene1.Load("Assets/Scenes/scene3.rsc");

    while (window_->IsActive())
    {
        ret::Time::Update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        cam.transform.position = glm::vec3(-2, cos(ret::Time::GetTime()) * 0.9f, 0);
        box.transform.position = glm::vec3(-2, 0, cos(ret::Time::GetTime()) * 0.9f);

        UpdateScenes();
        
        renderer.Draw();
    }

    delete window_;

    return 0;
}

void ret::RetEngine::UpdateScenes()
{
    for (unsigned int i = 0; i < scenes_.size(); i++)
    {
        scenes_[i].UpdateEntities();
    }
}
