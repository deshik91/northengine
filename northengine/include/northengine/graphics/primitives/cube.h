//
// Created by deshik on 25.01.2023.
//

#ifndef NORTH_ENGINE_LANG_CUBE_H
#define NORTH_ENGINE_LANG_CUBE_H

#include <glm/vec2.hpp>

#include "northengine/graphics/meshData.h"
#include "northengine/graphics/primitives/polygon.h"

MeshData CreateCube(glm::vec3 position, glm::vec3 size){
    MeshData meshData;

    meshData.AddMeshData(XPolygon(position, glm::vec2(size.y, size.z)));
    meshData.AddMeshData(XPolygon(glm::vec3(position.x + size.x, position.y, position.z), glm::vec2(size.y, size.z)));

    meshData.AddMeshData(YPolygon(glm::vec3(position.x, position.y + size.y, position.z), glm::vec2(size.x, size.z)));
    meshData.AddMeshData(YPolygon(glm::vec3(position.x, position.y, position.z), glm::vec2(size.x, size.z)));

    meshData.AddMeshData(ZPolygon(glm::vec3(position.x, position.y, position.z + size.z), glm::vec2(size.x, size.y)));
    meshData.AddMeshData(ZPolygon(glm::vec3(position.x, position.y, position.z), glm::vec2(size.x, size.y)));

    return meshData;
}

#endif //NORTH_ENGINE_LANG_CUBE_H
