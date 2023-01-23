//
// Created by deshik on 23.01.2023.
//
#include "northengine/graphics/mesh.h"

#include <glad/glad.h>

Mesh::Mesh(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount) {
    this->m_vertices = vertices;
    this->m_verticesCount = verticesCount;
    this->m_indices = indices;
    this->m_indicesCount = indicesCount;
}

Mesh::Mesh() {
    this->m_vertices = nullptr;
    this->m_verticesCount = 0;
    this->m_indices = nullptr;
    this->m_indicesCount = 0;
}

Mesh::~Mesh() {
    this->ClearData();
    this->ClearBuffers();
}

void Mesh::Draw() {
    if (m_VAO == 0)
        return;

    Bind();
    glDrawElements(GL_TRIANGLES, this->m_indicesCount, GL_UNSIGNED_INT, nullptr);
}

void Mesh::SetVertices(float *vertices, size_t verticesCount) {
    this->m_vertices = vertices;
    this->m_verticesCount = verticesCount;
}

void Mesh::SetIndices(unsigned int *indices, size_t indicesCount) {
    this->m_indices = indices;
    this->m_indicesCount = indicesCount;
}

float *Mesh::GetVertices() {
    return m_vertices;
}

unsigned int *Mesh::GetIndices() {
    return m_indices;
}

void Mesh::ClearData() {
    this->ClearVertices();
    this->ClearIndices();
}

void Mesh::ClearBuffers(){
    if (m_VAO != 0) {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }

    if (m_VBO != 0) {
        glDeleteBuffers(1, &m_VBO);
        m_VBO = 0;
    }

    if (m_EBO != 0) {
        glDeleteBuffers(1, &m_EBO);
        m_EBO = 0;
    }
}

void Mesh::ClearVertices() {
    if (this->m_vertices != nullptr) {
        delete[] this->m_vertices;
        this->m_vertices = nullptr;
    }
}

void Mesh::ClearIndices() {
    if (this->m_indices != nullptr) {
        delete[] this->m_indices;
        this->m_indices = nullptr;
    }
}

void Mesh::Bind() {
    glBindVertexArray(this->m_VAO);
}

void Mesh::GenerateBuffers() {
    if (m_verticesCount == 0)
        return;
    if (m_indicesCount == 0)
        return;

    if (m_VAO == 0)
        glGenVertexArrays(1, &m_VAO);
    if (m_VBO == 0)
        glGenBuffers(1, &m_VBO);
    if (m_EBO == 0)
        glGenBuffers(1, &m_EBO);

    if (m_VAO == 0 || m_VBO == 0 || m_EBO == 0)
        return;

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_verticesCount * sizeof(float), m_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indicesCount * sizeof(unsigned int), m_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void DrawMesh(Mesh *mesh, Shader *shader) {
    DrawMesh(*mesh, *shader);

}

void DrawMesh(Mesh &mesh, Shader &shader) {
    shader.Use();
    mesh.Draw();
}

void DrawMesh(Mesh *mesh, Shader &shader) {
    DrawMesh(*mesh, shader);
}

void DrawMesh(Mesh &mesh, Shader *shader) {
    DrawMesh(mesh, *shader);
}
