//
// Created by deshik on 23.01.2023.
//

#ifndef NORTH_ENGINE_LANG_CAMERA_H
#define NORTH_ENGINE_LANG_CAMERA_H

#include "northengine/graphics/shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    float m_yaw;
    float m_pitch;

    float m_mouseSensitivity;
    float m_zoom;

    bool m_yInverted;

    void UpdateCameraVectors();

public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);

    glm::mat4 GetViewMatrix();

    glm::mat4 GetProjectionMatrix(float width, float height);

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    float GetZoom();

    glm::vec3 GetPosition();

    glm::vec3 GetFront();

    glm::vec3 GetUp();

    glm::vec3 GetRight();

    glm::vec3 GetWorldUp();

    float GetYaw();

    float GetPitch();

    float GetMouseSensitivity();

    void UpdateShader(Shader *shader);

    void UpdateShader(Shader& shader);

    void SetPosition(glm::vec3 position);

    void Move(glm::vec3 direction);

    void Rotate(float xoffset, float yoffset, bool constrainPitch = true);

    void SetYaw(float yaw);

    void SetPitch(float pitch, bool constrainPitch = true);

    void SetZoom(float zoom);

    void AddZoom(float zoom);

    void MoveLocal(glm::vec3 direction);
};

#endif //NORTH_ENGINE_LANG_CAMERA_H
