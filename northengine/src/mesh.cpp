//
// Created by deshik on 23.01.2023.
//
#include "northengine/graphics/mesh.h"

#include <glad/glad.h>

Mesh::Mesh(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount) {
    m_meshData = new MeshData(vertices, verticesCount, indices, indicesCount);
}

Mesh::Mesh(MeshData *meshData) {
    m_meshData = meshData;
}

Mesh::Mesh(MeshData &meshData) {
    m_meshData = &meshData;
}

Mesh::Mesh() {
    m_meshData = new MeshData();
}

Mesh::~Mesh() {
    this->ClearData();
    this->ClearBuffers();
}

void Mesh::Draw() {
    if (m_VAO == 0)
        return;

    Bind();
    glDrawElements(GL_TRIANGLES, m_meshData->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::ClearBuffers() {
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

void Mesh::Bind() {
    glBindVertexArray(this->m_VAO);
}

void Mesh::GenerateBuffers() {
    float *vertices = nullptr;
    size_t verticesCount = 0;
    unsigned int *indices = nullptr;
    size_t indicesCount = 0;

    m_meshData->GetVertices(&vertices, verticesCount);
    m_meshData->GetIndices(&indices, indicesCount);

    if (verticesCount == 0)
        return;
    if (indicesCount == 0)
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
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::RefreshBuffers() {
    this->ClearBuffers();
    this->GenerateBuffers();
}

void Mesh::SetMeshData(MeshData *meshData) {
    this->ClearData();
    m_meshData = meshData;
}

void Mesh::SetMeshData(MeshData &meshData) {
    this->ClearData();
    m_meshData = &meshData;
}

MeshData *Mesh::GetMeshData() {
    return m_meshData;
}

void Mesh::ClearData() {
    if (m_meshData != nullptr) {
        delete m_meshData;
        m_meshData = nullptr;
    }
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
