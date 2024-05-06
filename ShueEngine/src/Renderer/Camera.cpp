#include "Camera.h"

#include "Application/Application.h"

namespace Shue {

    Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
        : Position(position), Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(up), Yaw(yaw), Pitch(pitch),
          MovementSpeed(2.5f), MouseSensitivity(0.1f), m_Movement(glm::vec3(0.0f)), m_CanControl(false)
    {
        UpdateCameraVectors();
    }

    Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
        : Position(glm::vec3(posX, posY, posZ)), Front(glm::vec3(0.0f, 0.0f, -1.0f)), WorldUp(glm::vec3(upX, upY, upZ)),
        Yaw(yaw), Pitch(pitch), MovementSpeed(2.5f), MouseSensitivity(0.1f), m_Movement(glm::vec3(0.0f)), m_CanControl(false)
    {
        UpdateCameraVectors();
    }

    void Camera::ProcessPressedKey(unsigned int keyCode)
    {
        if (keyCode == W)
            m_Movement = Front;
        if (keyCode == S)
            m_Movement = -Front;
        if (keyCode == A)
            m_Movement = -Right;
        if (keyCode == D)
            m_Movement = Right;
    }

    void Camera::ProcessReleasedKey(unsigned int keyCode)
    {
        if (keyCode == W || keyCode == S)
            m_Movement = glm::vec3(0.0f);
        if (keyCode == A || keyCode == D)
            m_Movement = glm::vec3(0.0f);
    }

    void Camera::ProcessPressedMouseButton(unsigned int button)
    {
        if (button == 1)
            m_CanControl = true;
    }

    void Camera::ProcessReleasedMouseButton(unsigned int button)
    {
        if (button == 1)
            m_CanControl = false;
    }

    void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
    {
        if (!m_CanControl)
            return;

		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch)
		{
			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
		}

		UpdateCameraVectors();
    }

    void Camera::OnUpdate()
    {
        if (!m_CanControl)
            return;

		float velocity = MovementSpeed * DELTA_TIME;
		Position += velocity * m_Movement;
    }

    void Camera::UpdateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }

}