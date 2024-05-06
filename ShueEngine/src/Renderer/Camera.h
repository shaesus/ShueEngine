#pragma once

#include "Core.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Shue {

    enum KeyCode {
        W = 87,
        A = 65,
        S = 83,
        D = 68
    };

    class SHUE_API Camera
    {
    public:
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = -90.0f, float pitch = 0.0f);

        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        inline glm::mat4 GetViewMatrix() const { return glm::lookAt(Position, Position + Front, Up); }

        void ProcessPressedKey(unsigned int keyCode);
        void ProcessReleasedKey(unsigned int keyCode);
        void ProcessPressedMouseButton(unsigned int button);
        void ProcessReleasedMouseButton(unsigned int button);
        void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

        void OnUpdate();

    public:
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;

    private:
        void UpdateCameraVectors();

    private:
        glm::vec3 m_Movement;

        bool m_CanControl;
    };

}