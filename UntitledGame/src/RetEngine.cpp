#include "RetEngine.h"
#include "retTime.h"
#include <glad/glad.h>
#include <iostream>

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

    Entity tree;
    Model fatTree("Assets/Models/fattree.obj");
    renderer.AddModel(&fatTree);
    tree.AddComponent(&fatTree);
    entities_.push_back(tree);

    Entity box;
    Model cube;
    renderer.AddModel(&cube);
    box.AddComponent(&cube);
    entities_.push_back(box);

    Shader* shader1 = ret::ShaderManager::GetShader("error_shader");

    while (window_->IsActive())
    {
        ret::Time::Update();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        UpdateEntities();
        
        renderer.Draw();
    }

    delete window_;

    return 0;
}

void ret::RetEngine::UpdateEntities()
{
    for (unsigned int i = 0; i < entities_.size(); i++)
    {
        if (entities_[i].isEnabled())
            entities_[i].Update();
    }
}