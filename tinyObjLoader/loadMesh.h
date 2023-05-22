#define TINYOBJLOADER_IMPLEMENTATION

#include <iostream>
#include <list>
#include "tiny_obj_loader.h"
#include "../ThreeD/Mesh.hpp"
#include "../math/Vector2.hpp"
#include "../math/Vector3.hpp"


std::list<Math::Vector2> compToVec2(const std::vector<float>& components) {
    auto vectors = std::list<Math::Vector2>();

    for(int i = 0; i < components.size(); i+=2) {
        vectors.emplace_back(
                components[i],
                components[i+1]
                );
    }

    return vectors;
}

std::list<Math::Vector3> compToVec3(const std::vector<float>& components) {
    auto vectors = std::list<Math::Vector3>();

    for(int i = 0; i < components.size(); i+=3) {
        vectors.emplace_back(
                components[i],
                components[i+1],
                components[i+2]
                );
    }

    return vectors;
}

//TODO: Load material
//See: https://github.com/canmom/rasteriser/blob/master/fileloader.cpp
void loadMesh(ThreeD::Mesh* output , const char* inputFile, const char* materials_directory){
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> objmaterials;
    std::string err;
    std::string warn;

    std::cout << "Loading model: " << inputFile << std::endl;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &objmaterials,
                                &warn, &err,
                                inputFile, //model to load
                                materials_directory //directory to search for materials
                                 );

    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    std::list<Math::Vector3> positions = compToVec3(attrib.vertices);
    std::list<Math::Vector3> normals = compToVec3(attrib.normals);
    std::list<Math::Vector2> texcoords = compToVec2(attrib.texcoords);

    output->vertexCount = attrib.vertices.size()/3;
    output->vertices = new ThreeD::Vertex[output->vertexCount];

    for (int i = 0; i < output->vertexCount; ++i) {
        output->vertices[i].position = positions.front();
        positions.pop_front();

        output->vertices[i].normal = normals.front();
        normals.pop_front();

        output->vertices[i].texcoords = texcoords.front();
        texcoords.pop_front();
    }

    output->indicesCount = shapes[0].mesh.indices.size();
    output->indices = new uint16_t [output->indicesCount];
    for (int i = 0; i < output->indicesCount; ++i) {
        output->indices[i] = shapes[0].mesh.indices[i].vertex_index;
    }

    //TODO: (Mais un peu compliqué, bonus si il nous reste du temps) Mono material
    for (auto mat = objmaterials.begin(); mat < objmaterials.end(); ++mat) {
        output->material.ambient = Math::Vector3(mat->ambient[0], mat->ambient[1], mat->ambient[2]);
        output->material.diffuse = Math::Vector3(mat->diffuse[0], mat->diffuse[1], mat->diffuse[2]);
        output->material.specular = Math::Vector3(mat->specular[0], mat->specular[1], mat->specular[2]);
        output->material.shininess = mat->shininess;
    }

    std::cout << "Model loaded: " << warn << std::endl;
}