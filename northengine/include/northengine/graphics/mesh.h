//
// Created by deshik on 23.01.2023.
//

#ifndef NORTH_ENGINE_LANG_MESH_H
#define NORTH_ENGINE_LANG_MESH_H

#include "northengine/graphics/meshData.h"

#include <cstdlib>

class Mesh {
private:
    MeshData *m_meshData = nullptr;

    unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;

public:
    Mesh(float *vertices, size_t verticesCount, unsigned int *indices, size_t indicesCount);

    Mesh(MeshData *meshData);

    Mesh(MeshData &meshData);

    Mesh();

    ~Mesh();

    void Draw();

    void ClearBuffers();

    void SetMeshData(MeshData *meshData);

    void SetMeshData(MeshData &meshData);

    MeshData *GetMeshData();

    void ClearData();

    void GenerateBuffers();

    void RefreshBuffers();

    void Bind();
};

#include "northengine/graphics/shader.h"

void DrawMesh(Mesh *mesh, Shader *shader);

void DrawMesh(Mesh &mesh, Shader &shader);

void DrawMesh(Mesh *mesh, Shader &shader);

void DrawMesh(Mesh &mesh, Shader *shader);


#endif //NORTH_ENGINE_LANG_MESH_H
