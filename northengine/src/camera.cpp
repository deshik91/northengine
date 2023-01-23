//
// Created by deshik on 23.01.2023.
//

#include "northengine/camera.h"

#include <cmath>

void Camera::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    front.y = sin(glm::radians(this->m_pitch));
    front.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
    this->m_front = glm::normalize(front);
    this->m_right = glm::normalize(glm::cross(this->m_front, this->m_worldUp));
    this->m_up = glm::normalize(glm::cross(this->m_right, this->m_front));
}

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) {
    this->m_position = position;
    this->m_worldUp = up;
    this->m_yaw = yaw;
    this->m_pitch = pitch;
    this->m_mouseSensitivity = 0.1f;
    this->m_zoom = 45.0f;
    this->m_yInverted = true;
    this->UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() {
    return glm::lookAt(this->m_position, this->m_position + this->m_front, this->m_up);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= this->m_mouseSensitivity;
    yoffset *= this->m_mouseSensitivity;

    this->m_yaw += xoffset;
    this->m_pitch += yoffset * (this->m_yInverted ? -1 : 1);

    if (constrainPitch) {
        if (this->m_pitch > 89.0f) {
            this->m_pitch = 89.0f;
        }
        if (this->m_pitch < -89.0f) {
            this->m_pitch = -89.0f;
        }
    }

    this->UpdateCameraVectors();
}


float Camera::GetZoom() {
    return this->m_zoom;
}

glm::vec3 Camera::GetPosition() {
    return this->m_position;
}

glm::vec3 Camera::GetFront() {
    return this->m_front;
}

glm::vec3 Camera::GetUp() {
    return this->m_up;
}

glm::vec3 Camera::GetRight() {
    return this->m_right;
}

glm::vec3 Camera::GetWorldUp() {
    return this->m_worldUp;
}

float Camera::GetYaw() {
    return this->m_yaw;
}

float Camera::GetPitch() {
    return this->m_pitch;
}

float Camera::GetMouseSensitivity() {
    return this->m_mouseSensitivity;
}

void Camera::UpdateShader(Shader *shader) {
    UpdateShader(shader);
}

void Camera::UpdateShader(Shader &shader) {
    shader.SetMat4("view", this->GetViewMatrix());
}

glm::mat4 Camera::GetProjectionMatrix(float width, float height) {
    return glm::perspective(glm::radians(this->m_zoom), width / height, 0.1f, 100.0f);
}

void Camera::SetPosition(glm::vec3 position) {
    this->m_position = position;
}

void Camera::Move(glm::vec3 direction) {
    this->m_position += direction;
}

void Camera::MoveLocal(glm::vec3 direction) {
    this->m_position += this->m_front * direction.z;
    this->m_position += this->m_right * direction.x;
    this->m_position += this->m_up * direction.y;
}

void Camera::Rotate(float xoffset, float yoffset, bool constrainPitch) {
    this->m_yaw += xoffset;
    this->m_pitch += yoffset;

    if (constrainPitch) {
        if (this->m_pitch > 89.0f) {
            this->m_pitch = 89.0f;
        }
        if (this->m_pitch < -89.0f) {
            this->m_pitch = -89.0f;
        }
    }

    this->UpdateCameraVectors();
}

void Camera::SetYaw(float yaw) {
    this->m_yaw = yaw;

    this->UpdateCameraVectors();
}

void Camera::SetPitch(float pitch, bool constrainPitch) {
    this->m_pitch = pitch;

    if (constrainPitch) {
        if (this->m_pitch > 89.0f) {
            this->m_pitch = 89.0f;
        }
        if (this->m_pitch < -89.0f) {
            this->m_pitch = -89.0f;
        }
    }

    this->UpdateCameraVectors();
}

void Camera::SetZoom(float zoom) {
    this->m_zoom = zoom;

    if (this->m_zoom < 0.2f) {
        this->m_zoom = 0.2f;
    }
}

void Camera::AddZoom(float zoom) {
    this->m_zoom += zoom;

    if (this->m_zoom < 0.2f) {
        this->m_zoom = 0.2f;
    }
}

