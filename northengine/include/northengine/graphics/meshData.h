//
// Created by deshik on 23.01.2023.
//

#ifndef NORTH_ENGINE_LANG_MESHDATA_H
#define NORTH_ENGINE_LANG_MESHDATA_H

#include <glm/glm.hpp>

#include <cstdlib>

class MeshData {
private:
    float *m_vertices = nullptr;
    size_t m_verticesCount = 0;

    unsigned int *m_indices = nullptr;
    size_t m_indicesCount = 0;

public:
    MeshData(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount);

    MeshData();

    ~MeshData();

    size_t GetVerticesCount();

    size_t GetIndicesCount();

    void GetVertices(float **vertices, size_t &verticesCount);

    void GetIndices(unsigned int **indices, size_t &indicesCount);

    void SetVertices(float *vertices, size_t verticesCount);

    void SetIndices(unsigned int *indices, size_t indicesCount);

    void ClearData();

    void ClearVertices();

    void ClearIndices();

    void AddVertices(float *vertices, size_t verticesCount);

    void AddIndices(unsigned int *indices, size_t indicesCount);

    // TODO: Fix AddVertex and AddIndex methods
    void AddVertex(float x, float y, float z, float u, float v);

    void AddVertex(glm::vec3 position, glm::vec2 uv);

    void AddVertex(glm::vec3 position);

    void AddVertex(float x, float y, float z);

    void AddIndex(unsigned int index);

    void AddMeshData(MeshData *meshData);

    void AddMeshData(MeshData &meshData);

    void AddMeshData(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount);
};

#endif //NORTH_ENGINE_LANG_MESHDATA_H
