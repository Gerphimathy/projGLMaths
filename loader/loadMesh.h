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
void loadObjMesh(ThreeD::Mesh* output , const char* inputFile, const char* materials_directory, bool verbose = false){
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> objmaterials;
    std::string err;
    std::string warn;

    if(verbose) std::cout << std::endl <<"Loading model: " << inputFile << std::endl;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &objmaterials,
                                &warn, &err,
                                inputFile, //model to load
                                materials_directory, //directory to search for materials
                        true);
    if(verbose) std::cout << ".obj loaded."<< std::endl;

    if (!err.empty()) { // `err` may contain warning message.
        std::cout << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    if (verbose) std::cout << "Loading vertices..."<< std::endl;

    std::vector<Math::Vector3> positions = compToVec3(attrib.vertices);
    std::vector<Math::Vector3> normals = compToVec3(attrib.normals);
    std::vector<Math::Vector2> texcoords = compToVec2(attrib.texcoords);

    output->vertexCount = positions.size();
    output->normalCount = normals.size();
    output->uvCount = texcoords.size();

    if(verbose) std::cout << "Loading: " << output->vertexCount << " vertices, " << output->normalCount << " normals, " << output->uvCount << " uvs" << std::endl;

    output->vertices = new Math::Vector3[output->vertexCount];
    output->normals = new Math::Vector3[output->normalCount];
    output->uvs = new Math::Vector2[output->uvCount];

    //Copy the data from the vectors to the arrays
    for(int i = 0; i < output->vertexCount; i++){
        output->vertices[i] = positions[i];
    }

    for(int i = 0; i < output->normalCount; i++){
        output->normals[i] = normals[i];
    }

    for(int i = 0; i < output->uvCount; i++){
        output->uvs[i] = texcoords[i];
    }
    if(verbose) std::cout << "Vertices loaded" << std::endl;
    if(verbose) std::cout << "Loading triangles..." << std::endl;

    //Count the number of triangles
    output->triangleCount = 0;
    for(auto shape = shapes.begin(); shape < shapes.end(); ++shape){
        output->triangleCount += shape->mesh.num_face_vertices.size();
    }
    if(verbose) std::cout << "Triangle count: " << output->triangleCount << std::endl;
    output->triangles = new ThreeD::Triangle[output->triangleCount];

    int triangleIndex = 0;
    for(auto shape = shapes.begin(); shape < shapes.end(); ++shape){
        for(auto triangle = shape->mesh.num_face_vertices.begin(); triangle < shape->mesh.num_face_vertices.end(); ++triangle){
            if(*triangle != 3){
                std::cerr << "Non-triangle face detected" << std::endl;
                exit(-1);
            }
            //Get the indices for the triangle
            for(int i = 0; i < 3; i++){
                tinyobj::index_t idx = shape->mesh.indices[triangleIndex*3 + i];
                output->triangles[triangleIndex].vertex_indices[i] = idx.vertex_index;
                output->triangles[triangleIndex].normal_indices[i] = idx.normal_index;
                output->triangles[triangleIndex].uv_indices[i] = idx.texcoord_index;
            }
            output->triangles[triangleIndex].material_index = shape->mesh.material_ids[triangleIndex];
            triangleIndex++;
        }
        //Get material index for the face + all indices for the face
    }
    if(verbose) std::cout << "Triangles loaded" << std::endl;

    output->materialCount = objmaterials.size();
    output->materials = new ThreeD::Material[output->materialCount];

    if(verbose) std::cout << "Loading materials: " << output->materialCount << " materials" << std::endl;
    int j = 0;
    for (auto mat = objmaterials.begin(); mat < objmaterials.end(); ++mat) {
        if(verbose) std::cout << "Loading material " << mat->name << " as material " << j << std::endl;
        output->materials[j].name = mat->name;

        output->materials[j].ambient.x = mat->ambient[0];
        output->materials[j].ambient.y = mat->ambient[1];
        output->materials[j].ambient.z = mat->ambient[2];

        output->materials[j].diffuse.x = mat->diffuse[0];
        output->materials[j].diffuse.y = mat->diffuse[1];
        output->materials[j].diffuse.z = mat->diffuse[2];

        output->materials[j].specular.x = mat->specular[0];
        output->materials[j].specular.y = mat->specular[1];
        output->materials[j].specular.z = mat->specular[2];

        output->materials[j].shininess = mat->shininess;
        if(verbose) std::cout << "Material " << j << " loaded" << std::endl;

        if(!mat->diffuse_texname.empty()){
            if(verbose) std::cout << "Loading texture..." << std::endl;
            output->materials[j].texture = new ThreeD::Texture();
            output->materials[j].texture->path = std::string(materials_directory) + mat->diffuse_texname;

            unsigned char* data = stbi_load(output->materials[j].texture->path.c_str(),
                                                       &output->materials[j].texture->width,
                                                       &output->materials[j].texture->height,
                                                       &output->materials[j].texture->channels,
                                                       STBI_rgb_alpha);

            if (data){
                unsigned int textureId;
                glGenTextures(1, &textureId);
                glBindTexture(GL_TEXTURE_2D, textureId);

                output->materials[j].texture->id = textureId;

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
                             output->materials[j].texture->width, output->materials[j].texture->height,
                             0, GL_RGBA, GL_UNSIGNED_BYTE,
                             data);

                glGenerateMipmap(GL_TEXTURE_2D);

                stbi_image_free(data);

                if(verbose) std::cout << "Texture loaded."<< std::endl;
            }else if(verbose) std::cout << "Failed to load texture: " << output->materials[j].texture->path << std::endl;
        }
        j++;
    }

    positions.clear();
    normals.clear();
    texcoords.clear();
    shapes.clear();
    objmaterials.clear();

    if(verbose) std::cout << "Model loaded " << warn << std::endl << std::endl;
}