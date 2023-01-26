//
// Created by deshik on 25.01.2023.
//

#ifndef NORTH_ENGINE_LANG_POLYGON_H
#define NORTH_ENGINE_LANG_POLYGON_H

#include <glm/vec2.hpp>

#include "northengine/graphics/meshData.h"

MeshData XPolygon(glm::vec3 position, glm::vec2 size, glm::vec2 uv) {
    MeshData meshData;
    meshData.AddVertex(position.x, position.y, position.z, uv.x, uv.y);
    meshData.AddVertex(position.x, position.y, position.z + size.x, uv.x + size.x, uv.y);
    meshData.AddVertex(position.x, position.y + size.y, position.z + size.x, uv.x + size.x, uv.y + size.y);
    meshData.AddVertex(position.x, position.y + size.y, position.z, uv.x, uv.y + size.y);
    meshData.AddIndex(0);
    meshData.AddIndex(1);
    meshData.AddIndex(2);
    meshData.AddIndex(2);
    meshData.AddIndex(3);
    meshData.AddIndex(0);
    return meshData;
}

MeshData XPolygon(glm::vec3 position, glm::vec2 size) {
    return XPolygon(position, size, glm::vec2(0, 0));
}

MeshData YPolygon(glm::vec3 position, glm::vec2 size, glm::vec2 uv) {
    MeshData meshData;
    meshData.AddVertex(position.x, position.y, position.z, uv.x, uv.y);
    meshData.AddVertex(position.x + size.x, position.y, position.z, uv.x + size.x, uv.y);
    meshData.AddVertex(position.x + size.x, position.y, position.z + size.y, uv.x + size.x, uv.y + size.y);
    meshData.AddVertex(position.x, position.y, position.z + size.y, uv.x, uv.y + size.y);
    meshData.AddIndex(0);
    meshData.AddIndex(1);
    meshData.AddIndex(2);
    meshData.AddIndex(2);
    meshData.AddIndex(3);
    meshData.AddIndex(0);
    return meshData;
}

MeshData YPolygon(glm::vec3 position, glm::vec2 size) {
    return YPolygon(position, size, glm::vec2(0, 0));
}

MeshData ZPolygon(glm::vec3 position, glm::vec2 size, glm::vec2 uv) {
    MeshData meshData;
    meshData.AddVertex(position.x, position.y, position.z, uv.x, uv.y);
    meshData.AddVertex(position.x + size.x, position.y, position.z, uv.x + size.x, uv.y);
    meshData.AddVertex(position.x + size.x, position.y + size.y, position.z, uv.x + size.x, uv.y + size.y);
    meshData.AddVertex(position.x, position.y + size.y, position.z, uv.x, uv.y + size.y);
    meshData.AddIndex(0);
    meshData.AddIndex(1);
    meshData.AddIndex(2);
    meshData.AddIndex(2);
    meshData.AddIndex(3);
    meshData.AddIndex(0);
    return meshData;
}

MeshData ZPolygon(glm::vec3 position, glm::vec2 size) {
    return ZPolygon(position, size, glm::vec2(0, 0));
}

#endif //NORTH_ENGINE_LANG_POLYGON_H
