#include "Camera.h"
#include "Entity.h"
#include <glm/gtc/matrix_transform.hpp>

ret::Camera::Camera(glm::vec3 t_pos, glm::vec3 t_rot)
{
    posOffset = t_pos;
    rotation = t_rot;
	worldUp_ = glm::vec3(0, 1, 0);

    UpdateCameraVectors();
}

glm::mat4 ret::Camera::GetViewMatrix()
{
	if(entity != nullptr)
		return glm::lookAt(posOffset + entity->transform.position, posOffset + entity->transform.position + front_, up_);
	else
		return glm::lookAt(posOffset, posOffset + front_, up_);
}

void ret::Camera::UpdateCameraVectors()
{
	glm::vec3 tFront;
	tFront.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	tFront.y = sin(glm::radians(rotation.x));
	tFront.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));

	front_ = glm::normalize(tFront);

	if (rotation.x < 270.0f && rotation.x > 90.0f)
		right_ = glm::normalize(glm::cross(front_, -worldUp_));
	else
		right_ = glm::normalize(glm::cross(front_, worldUp_));

	up_ = glm::normalize(glm::cross(right_, front_));
}
