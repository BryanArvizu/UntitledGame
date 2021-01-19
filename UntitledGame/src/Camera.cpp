#include "Camera.h"
#include "Entity.h"
#include <glm/glm.hpp>
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
	if (entity != nullptr)
	{
		return glm::lookAt(posOffset + entity->transform.position, posOffset + entity->transform.position + front_, up_);
	}
	else
		return glm::lookAt(posOffset, posOffset + front_, up_);
}

void ret::Camera::Rotate(float t_xoffset, float t_yoffset, GLboolean t_constrainPitch)
{
	// There may be a bug with the math here, where higher sensitivities make the camera wonky
	rotation.x = glm::mod(rotation.x + t_yoffset, 360.0f);
	rotation.y = glm::mod(rotation.y + t_xoffset, 360.0f);

	//std::cout << "YAW: " << yaw << " | " << "PITCH: " << pitch << std::endl;

	if (t_constrainPitch)
	{
		if (rotation.y < 180.0f)
			rotation.y = glm::clamp(rotation.y, -89.0f, 89.0f);
		else
			rotation.y = glm::clamp(rotation.y, 271.0f, 449.0f);
	}

	UpdateCameraVectors();
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
