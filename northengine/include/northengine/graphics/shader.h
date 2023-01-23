//
// Created by deshik on 21.01.2023.
// Copied from https://github.com/JoeyDeVries/LearnOpenGL/blob/master/includes/learnopengl/shader.h
//

#ifndef NORTH_ENGINE_LANG_SHADER_H
#define NORTH_ENGINE_LANG_SHADER_H

#include "northengine/graphics/texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader(const char *vertexPath, const char *fragmentPath, const char *geometryPath = nullptr);

    void Use() const;

    void SetBool(const std::string &name, bool value) const;

    void SetInt(const std::string &name, int value) const;

    void SetFloat(const std::string &name, float value) const;

    void SetVec2(const std::string &name, const glm::vec2 &value) const;

    void SetVec2(const std::string &name, float x, float y) const;

    void SetVec3(const std::string &name, const glm::vec3 &value) const;

    void SetVec3(const std::string &name, float x, float y, float z) const;

    void SetVec4(const std::string &name, const glm::vec4 &value) const;

    void SetVec4(const std::string &name, float x, float y, float z, float w);

    void SetMat2(const std::string &name, const glm::mat2 &mat) const;

    void SetMat3(const std::string &name, const glm::mat3 &mat) const;

    void SetMat4(const std::string &name, const glm::mat4 &mat) const;

    void SetTexture(const std::string &name, int value) const;

    void SetTexture(const std::string &name, Texture &texture) const;

private:
    void CheckCompileErrors(GLuint shader, std::string type);
};

#endif //NORTH_ENGINE_LANG_SHADER_H
