#include "Renderer.h"

#include "Shader.h"
#include "Texture.h"

#include "../Component/Render.h"
#include "../Component/Model.h"
#include "../Component/Mesh.h"
#include "../Camera.h"
#include "../Entity.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../retTime.h"

ret::Renderer::Renderer() : renderList()
{
    defaultShader = ret::ShaderManager::GetShader("error_shader");
}

ret::Renderer::~Renderer()
{
}

void ret::Renderer::Draw()
{
    glClearColor(0.0f, 0.1f, 0.2f, 0.1f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (unsigned int i = 0; i < renderList.size(); i++)
    {
        DrawModel(renderList[i]->model, renderList[i]->entity->transform, renderList[i]->mat);
    }
}

bool ret::Renderer::Add(Render* t_renderPtr)
{
    for (unsigned int i = 0; i < renderList.size(); i++)
    {
        if (t_renderPtr == renderList[i])
            return false;
    }
    renderList.push_back(t_renderPtr);
    return true;
}

bool ret::Renderer::Remove(Render* t_renderPtr)
{
    for (unsigned int i = 0; i < renderList.size(); i++)
    {
        if (t_renderPtr == renderList[i])
        {
            renderList.erase(renderList.begin() + i);
            return true;
        }
    }
    return false;
}

void ret::Renderer::DrawModel(const Model* t_modelPtr, const Transform &t_transform, const Material* t_material)
{
    for (unsigned int i = 0; i < t_modelPtr->meshes.size(); i++)
    {
        DrawMesh(t_modelPtr->meshes[i], t_transform, t_material);
    }
}

void ret::Renderer::DrawMesh(const Mesh &mesh, const Transform &transform, const Material* &t_material)
{
    Shader* shader = defaultShader;
    
    if (mesh.material != nullptr && mesh.material->shader != nullptr)
    {
        shader = mesh.material->shader;
    }
    else if (t_material != nullptr && t_material->shader != nullptr)
    {
        shader = t_material->shader;
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