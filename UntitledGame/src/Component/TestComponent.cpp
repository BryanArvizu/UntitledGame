#include "TestComponent.h"
#include "../RetEngine.h"
#include "../retTime.h"
#include <GLFW/glfw3.h>

void ret::TestComponent::Start()
{
    window = ret::RetEngine::Get()->window_->GetGLFWWindow();
    entity->GetComponent<Camera>(camera);
}

void ret::TestComponent::Update()
{
    UpdateCamera();
    UpdateMovement();
}

void ret::TestComponent::UpdateMovement()
{
    float speed = 10.0f;

    glm::vec3 movement(0.0f);

    {
        if (glfwGetKey(window, GLFW_KEY_W))
            movement.z += 1;
        if (glfwGetKey(window, GLFW_KEY_S))
            movement.z -= 1;
        if (glfwGetKey(window, GLFW_KEY_A))
            movement.x -= 1;
        if (glfwGetKey(window, GLFW_KEY_D))
            movement.x += 1;
        if (glfwGetKey(window, GLFW_KEY_SPACE))
            movement.y += 1;
        if (glfwGetKey(window, GLFW_KEY_C))
            movement.y -= 1;
    }

    if (movement != glm::vec3(0.0f))
    {
        glm::normalize(movement);

        if (camera != nullptr)
        {
            glm::vec3 adjustedMovement = glm::vec3(0.0f);
            adjustedMovement += movement.x * camera->right_;
            adjustedMovement += movement.y * camera->up_;
            adjustedMovement += movement.z * camera->front_;
            movement = adjustedMovement;
        }

        entity->transform.position += movement * speed * (float)ret::Time::GetDeltaTime();
        std::cout << "Position: (" << entity->transform.position.x << ", "
                  << entity->transform.position.y << ", "
                  << entity->transform.position.z << ") " << std::endl;
    }
}

void ret::TestComponent::UpdateCamera()
{
    if (camera != nullptr)
    {
        float speed = 10.0f;

        glm::vec3 movement(0.0f);

        if (glfwGetKey(window, GLFW_KEY_UP))
        {
            movement.y += 1;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN))
        {
            movement.y -= 1;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT))
        {
            movement.x -= 1;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT))
        {
            movement.x += 1;
        }
        if (movement != glm::vec3(0.0f))
        {
            camera->Rotate(movement.x, movement.y, false);
        }
    }
}
