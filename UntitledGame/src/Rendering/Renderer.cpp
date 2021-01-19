#include "Renderer.h"

#include "Shader.h"
#include "Texture.h"

#include "../Component/Model.h"
#include "../Component/Mesh.h"
#include "../Camera.h"
#include "../Entity.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../retTime.h"

std::vector<ret::Renderer*> ret::Renderer::renderers;

ret::Renderer::Renderer() : index(0), models_()
{
    int index = renderers.size();
    renderers.push_back(this);

    glClearColor(0.0f, 0.7f, 0.9f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    defaultShader = ret::ShaderManager::GetShader("error_shader");
}

ret::Renderer::~Renderer()
{
}

void ret::Renderer::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < models_.size(); i++)
    {
        DrawModel(models_[i]);
    }
}

bool ret::Renderer::AddModel(Model* t_modelPtr)
{
    for (unsigned int i = 0; i < models_.size(); i++)
    {
        if (t_modelPtr == models_[i])
            return false;
    }
    models_.push_back(t_modelPtr);
    return true;
}

bool ret::Renderer::RemoveModel(Model* t_modelPtr)
{
    for (unsigned int i = 0; i < models_.size(); i++)
    {
        if (t_modelPtr == models_[i])
        {
            models_.erase(models_.begin() + i);
            return true;
        }
    }
    return false;
}

void ret::Renderer::DrawModel(Model* &t_modelPtr)
{
    if (t_modelPtr->entity == nullptr)
        return;

    for (unsigned int i = 0; i < t_modelPtr->meshes.size(); i++)
    {
        DrawMesh(t_modelPtr->meshes[i], t_modelPtr->entity->transform);
    }
}

void ret::Renderer::DrawMesh(Mesh mesh, const Transform &transform)
{
    Shader* shader = defaultShader;
    
    if (mesh.material != nullptr && mesh.material->shader != nullptr)
    {
        shader = mesh.material->shader;
    }
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, transform.position);
    model = model * glm::mat4_cast(transform.rotation);
    model = glm::scale(model, transform.scale);

    glm::mat4 view;
    if (camera != nullptr)
    {
        view = camera->GetViewMatrix();
    }
    else
        view = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

    glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", proj);
    shader->setFloat("time", ret::Time::GetTime());

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    if(mesh.material != nullptr)
    {
        for (unsigned int i = 0; i < mesh.material->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);

            shader->setInt("texture" + std::to_string(i), i);

            glBindTexture(GL_TEXTURE_2D, mesh.material->textures[i]->id);
        }
    }

    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}