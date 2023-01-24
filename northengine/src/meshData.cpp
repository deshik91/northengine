//
// Created by deshik on 23.01.2023.
//

#ifndef NORTH_ENGINE_LANG_MESHDATA_CPP
#define NORTH_ENGINE_LANG_MESHDATA_CPP

#include "northengine/graphics/meshData.h"

#include <cstring>

MeshData::MeshData(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount) {
    SetVertices(vertices, verticesCount);
    SetIndices(indices, indicesCount);
}

MeshData::MeshData() {
    m_vertices = nullptr;
    m_verticesCount = 0;
    m_indices = nullptr;
    m_indicesCount = 0;
}

MeshData::~MeshData() {
    ClearData();
}

void MeshData::GetVertices(float **vertices, size_t &verticesCount) {
    *vertices = m_vertices;
    verticesCount = m_verticesCount;
}

void MeshData::GetIndices(unsigned int **indices, size_t &indicesCount) {
    *indices = m_indices;
    indicesCount = m_indicesCount;
}

void MeshData::SetVertices(float *vertices, size_t verticesCount) {
    ClearVertices();
    m_vertices = new float[verticesCount];
//    memcpy(m_vertices, vertices, verticesCount * sizeof(float));
    for (int i = 0; i < verticesCount; i++) {
        m_vertices[i] = vertices[i];
    }
    m_verticesCount = verticesCount;
}

void MeshData::SetIndices(unsigned int *indices, size_t indicesCount) {
    ClearIndices();
    m_indices = new unsigned int[indicesCount];
//    memcpy(m_indices, indices, indicesCount * sizeof(unsigned int));
    for (int i = 0; i < indicesCount; i++) {
        m_indices[i] = indices[i];
    }
    m_indicesCount = indicesCount;
}

void MeshData::ClearData() {
    ClearVertices();
    ClearIndices();
}

void MeshData::ClearVertices() {
    if (m_vertices != nullptr) {
        delete[] m_vertices;
        m_vertices = nullptr;
    }
    m_verticesCount = 0;
}

void MeshData::ClearIndices() {
    if (m_indices != nullptr) {
        delete[] m_indices;
        m_indices = nullptr;
    }
    m_indicesCount = 0;
}

void MeshData::AddVertices(float *vertices, size_t verticesCount) {
    if (m_vertices == nullptr) {
        SetVertices(vertices, verticesCount);
        return;
    }

    float *newVertices = new float[m_verticesCount + verticesCount];
    memcpy(newVertices, m_vertices, m_verticesCount * sizeof(float));
    memcpy(newVertices + m_verticesCount, vertices, verticesCount * sizeof(float));
    verticesCount += m_verticesCount;
    ClearVertices();
    m_vertices = newVertices;
    m_verticesCount += verticesCount;
}

void MeshData::AddIndices(unsigned int *indices, size_t indicesCount) {
    if (m_indices == nullptr) {
        SetIndices(indices, indicesCount);
        return;
    }

    unsigned int *newIndices = new unsigned int[m_indicesCount + indicesCount];
    memcpy(newIndices, m_indices, m_indicesCount * sizeof(unsigned int));
    memcpy(newIndices + m_indicesCount, indices, indicesCount * sizeof(unsigned int));
    indicesCount += m_indicesCount;
    ClearIndices();
    m_indices = newIndices;
    m_indicesCount += indicesCount;
}

void MeshData::AddMeshData(MeshData *meshData) {
    float *vertices;
    size_t verticesCount;
    meshData->GetVertices(&vertices, verticesCount);
    AddVertices(vertices, verticesCount);

    unsigned int *indices;
    size_t indicesCount;
    meshData->GetIndices(&indices, indicesCount);
    AddIndices(indices, indicesCount);
}

void MeshData::AddMeshData(MeshData &meshData) {
    AddMeshData(&meshData);
}

void MeshData::AddMeshData(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount) {
    AddVertices(vertices, verticesCount);
    AddIndices(indices, indicesCount);
}

size_t MeshData::GetVerticesCount() {
    return m_verticesCount;
}

size_t MeshData::GetIndicesCount() {
    return m_indicesCount;
}

void MeshData::AddVertex(float x, float y, float z, float u, float v) {
    float vertices[] = {x, y, z, u, v};
    AddVertices(vertices, 5);
}

void MeshData::AddVertex(glm::vec3 position, glm::vec2 uv) {
    AddVertex(position.x, position.y, position.z, uv.x, uv.y);
}

void MeshData::AddVertex(glm::vec3 position) {
    AddVertex(position.x, position.y, position.z, 0, 0);
}

void MeshData::AddVertex(float x, float y, float z) {
    AddVertex(x, y, z, 0, 0);
}

void MeshData::AddIndex(unsigned int index) {
    unsigned int indices[] = {index};
    AddIndices(indices, 1);
}

#endif //NORTH_ENGINE_LANG_MESHDATA_CPP
