#include "Renderer.h"
#include "ShaderManager.h"
#include "../Component/Model.h"
#include "../Component/Mesh.h"
#include "../Shader.h"
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
    std::cout << renderers.size() << std::endl;
}

ret::Renderer::~Renderer()
{
}

void ret::Renderer::Draw()
{
    std::cout << "Renderer::Draw() called" << std::endl;
    for (unsigned int i = 0; i < models_.size(); i++)
    {
        std::cout << "\tDrawing Model " << i << " " << std::endl;
        DrawModel(models_[i]);
    }
}

bool ret::Renderer::AddModel(Model* model)
{
    for (unsigned int i = 0; i < models_.size(); i++)
    {
        if (model == models_[i])
            return false;
    }
    models_.push_back(model);
    return true;
}

bool ret::Renderer::RemoveModel(Model* model)
{
    for (unsigned int i = 0; i < models_.size(); i++)
    {
        if (model == models_[i])
        {
            models_.erase(models_.begin() + i);
            return true;
        }
    }
    return false;
}

void ret::Renderer::DrawModel(Model* model)
{
    for (unsigned int i = 0; i < model->meshes.size(); i++)
    {
        std::cout << "\t\tDrawing Mesh " << i << " " << std::endl;
        DrawMesh(model->meshes[i]);
    }
}

void ret::Renderer::DrawMesh(Mesh mesh)
{
    Shader* shader;
    if(mesh.shaderPath.size() > 0)
        shader = ret::ShaderManager::GetShader(mesh.shaderPath);
    else
        shader = ret::ShaderManager::GetShader("error_shader");

    // TEMP STUFFS

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, -2.0f));
    model = glm::scale(model, glm::vec3(0.1f));

    glm::mat4 view = glm::lookAt(glm::vec3(0,0,0), glm::vec3(0,0,-1), glm::vec3(0,1,0));

    glm::mat4 proj = glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);

    shader->use();
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", proj);
    //

    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for (unsigned int i = 0; i < mesh.textures_.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string number;
        if (mesh.textures_[i].type == "diffuse")
        {
            number = std::to_string(diffuseNr++);
            shader->setFloat(("material.diffuse" + number), i);
        }
        else if (mesh.textures_[i].type == "specular")
        {
            number = std::to_string(specularNr++);
            shader->setFloat(("material.specular" + number), i);
        }

        glActiveTexture(GL_TEXTURE0);

    }
        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.indices_.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
}