#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <iostream>
#include <list>
#include "tiny_obj_loader.h"
#include "../ThreeD/Mesh.hpp"
#include "../math/Vector2.hpp"
#include "../math/Vector3.hpp"


std::vector<Math::Vector2> compToVec2(const std::vector<float>& components) {
    auto vectors = std::vector<Math::Vector2>();

    for(int i = 0; i < components.size(); i+=2) {
        vectors.emplace_back(
                components[i],
                components[i+1]
                );
    }

    return vectors;
}

std::vector<Math::Vector3> compToVec3(const std::vector<float>& components) {
    auto vectors = std::vector<Math::Vector3>();

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
void loadObjMesh(ThreeD::Mesh* output , const char* inputFile, const char* materials_directory){
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> objmaterials;
    std::string err;
    std::string warn;

    std::cout << "Loading model: " << inputFile << std::endl;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &objmaterials,
                                &warn, &err,
                                inputFile, //model to load
                                materials_directory, //directory to search for materials
                        true
                                 );

    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    std::vector<Math::Vector3> positions = compToVec3(attrib.vertices);
    std::vector<Math::Vector3> normals = compToVec3(attrib.normals);
    std::vector<Math::Vector2> texcoords = compToVec2(attrib.texcoords);

    output->vertexCount = 0;
    output->indicesCount = 0;
    for(auto shape = shapes.begin(); shape < shapes.end(); ++shape){
        output->vertexCount += shape->mesh.indices.size();
        output->indicesCount += shape->mesh.indices.size();
    }
    output->vertices = new ThreeD::Vertex[output->vertexCount];
    output->indices = new uint16_t [output->indicesCount];

    int vertexIndex = 0;
    for(auto shape = shapes.begin(); shape < shapes.end(); ++shape){
        for(auto index = shape->mesh.indices.begin(); index < shape->mesh.indices.end(); ++index){
            output->vertices[vertexIndex].position = positions[index->vertex_index];
            output->vertices[vertexIndex].normal = normals[index->normal_index];
            output->vertices[vertexIndex].texcoords = texcoords[index->texcoord_index];
            output->indices[vertexIndex] = vertexIndex;
            vertexIndex++;
        }
    }

    for (auto mat = objmaterials.begin(); mat < objmaterials.end(); ++mat) {
        output->material.ambient = Math::Vector3(mat->ambient[0], mat->ambient[1], mat->ambient[2]);
        output->material.diffuse = Math::Vector3(mat->diffuse[0], mat->diffuse[1], mat->diffuse[2]);
        output->material.specular = Math::Vector3(mat->specular[0], mat->specular[1], mat->specular[2]);
        output->material.shininess = mat->shininess;

        if(!mat->diffuse_texname.empty()){
            std::cout << "Loading texture..." << std::endl;
            output->material.texture = new ThreeD::Texture();
            output->material.texture->path = std::string(materials_directory) + mat->diffuse_texname;

            unsigned char* data = stbi_load(output->material.texture->path.c_str(),
                                                       &output->material.texture->width,
                                                       &output->material.texture->height,
                                                       &output->material.texture->channels,
                                                       STBI_rgb_alpha);

            if (data){
                unsigned int textureId;
                glGenTextures(1, &textureId);
                glBindTexture(GL_TEXTURE_2D, textureId);

                output->material.texture->id = textureId;

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                             output->material.texture->width, output->material.texture->height,
                             0, GL_RGBA, GL_UNSIGNED_BYTE,
                             data);

                glGenerateMipmap(GL_TEXTURE_2D);

                stbi_image_free(data);

                std::cout << "Texture loaded: " << output->material.texture->path << std::endl;
            }else std::cout << "Failed to load texture: " << output->material.texture->path << std::endl;
        }
    }

    std::cout << "Model loaded " << warn << std::endl << std::endl;
}