//
// Created by deshik on 23.01.2023.
//

#ifndef NORTH_ENGINE_LANG_MESH_H
#define NORTH_ENGINE_LANG_MESH_H

#include <cstdlib>

class Mesh {
private:
    float *m_vertices = nullptr;
    size_t m_verticesCount = 0;

    unsigned int *m_indices = nullptr;
    size_t m_indicesCount = 0;

    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;

public:
    Mesh(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount);
    Mesh();

    ~Mesh();

    void Draw();

    void SetVertices(float *vertices, size_t verticesCount);

    void SetIndices(unsigned int *indices, size_t indicesCount);

    float *GetVertices();

    unsigned int *GetIndices();

    void ClearData();

    void ClearVertices();

    void ClearIndices();

    void GenerateBuffers();

    void Bind();

    void ClearBuffers();
};

#include "northengine/graphics/shader.h"

void DrawMesh(Mesh *mesh, Shader *shader);

void DrawMesh(Mesh& mesh, Shader& shader);

void DrawMesh(Mesh *mesh, Shader& shader);

void DrawMesh(Mesh& mesh, Shader *shader);



#endif //NORTH_ENGINE_LANG_MESH_H
