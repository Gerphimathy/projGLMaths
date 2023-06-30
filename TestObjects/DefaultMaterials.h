#include "../ThreeD/Material.hpp"
#include <map>


std::map<std::string, ThreeD::Material*> defaultMaterials(){
    auto* jade = new ThreeD::Material();
    jade->name = "Jade";
    jade->ambient = Math::Vector3(0.135f, 0.2225f, 0.1575f);
    jade->diffuse = Math::Vector3(0.54f, 0.89f, 0.63f);
    jade->specular = Math::Vector3(0.316228f, 0.316228f, 0.316228f);
    jade->shininess = 128.0f;

    auto* emerald = new ThreeD::Material();
    emerald->name = "Emerald";
    emerald->ambient = Math::Vector3(0.0215f, 0.1745f, 0.0215f);
    emerald->diffuse = Math::Vector3(0.07568f, 0.61424f, 0.07568f);
    emerald->specular = Math::Vector3(0.633f, 0.727811f, 0.633f);
    emerald->shininess = 128.0f;

    auto* ruby = new ThreeD::Material();
    ruby->name = "Ruby";
    ruby->ambient = Math::Vector3(0.1745f, 0.01175f, 0.01175f);
    ruby->diffuse = Math::Vector3(0.61424f, 0.04136f, 0.04136f);
    ruby->specular = Math::Vector3(0.727811f, 0.626959f, 0.626959f);
    ruby->shininess = 128.0f;

    auto* gold = new ThreeD::Material();
    gold->name = "Gold";
    gold->ambient = Math::Vector3(0.24725f, 0.1995f, 0.0745f);
    gold->diffuse = Math::Vector3(0.75164f, 0.60648f, 0.22648f);
    gold->specular = Math::Vector3(0.628281f, 0.555802f, 0.366065f);
    gold->shininess = 128.0f;

    auto* silver = new ThreeD::Material();
    silver->name = "Silver";
    silver->ambient = Math::Vector3(0.19225f, 0.19225f, 0.19225f);
    silver->diffuse = Math::Vector3(0.50754f, 0.50754f, 0.50754f);
    silver->specular = Math::Vector3(0.508273f, 0.508273f, 0.508273f);
    silver->shininess = 128.0f;

    auto* ebony = new ThreeD::Material();
    ebony->name = "Ebony";
    ebony->ambient = Math::Vector3(0.0f, 0.0f, 0.0f);
    ebony->diffuse = Math::Vector3(0.1f, 0.1f, 0.1f);
    ebony->specular = Math::Vector3(0.5f, 0.5f, 0.5f);
    ebony->shininess = 128.0f;

    return {
        {"Jade", jade},
        {"Emerald", emerald},
        {"Ruby", ruby},
        {"Gold", gold},
        {"Silver", silver},
        {"Ebony", ebony}
    };
}