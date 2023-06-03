#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../ThreeD/Camera.h"

bool keyCodes[400];

void processControls(GLFWwindow* window, ThreeD::Camera* camera, float deltaTime){
    const float MOVE_SPEED = 20;
    const float CAM_SENSI = 1;

    if (keyCodes[GLFW_KEY_W]) {
        camera->position -= camera->forward() * MOVE_SPEED * deltaTime;
    }
    if (keyCodes[GLFW_KEY_S]) {
        camera->position += camera->forward() * MOVE_SPEED * deltaTime;
    }
    if (keyCodes[GLFW_KEY_A]) {
        camera->position -= camera->right() * MOVE_SPEED * deltaTime;
    }
    if (keyCodes[GLFW_KEY_D]) {
        camera->position += camera->right() * MOVE_SPEED * deltaTime;
    }
    if (keyCodes[GLFW_KEY_SPACE]){
        camera->position += camera->up() * MOVE_SPEED * deltaTime;
    }
    if (keyCodes[GLFW_KEY_LEFT_SHIFT]){
        camera->position -= camera->up() * MOVE_SPEED * deltaTime;
    }

    if (keyCodes[GLFW_KEY_UP]){
        camera->rotate(Math::Quaternion::Euler(CAM_SENSI * deltaTime,0,0));
    }

    if (keyCodes[GLFW_KEY_DOWN]){
        camera->rotate(Math::Quaternion::Euler(-CAM_SENSI * deltaTime,0,0));
    }

    if(keyCodes[GLFW_KEY_LEFT]){
        camera->rotate(Math::Quaternion::Euler(0,CAM_SENSI * deltaTime,0));
    }

    if(keyCodes[GLFW_KEY_RIGHT]){
        camera->rotate(Math::Quaternion::Euler(0,-CAM_SENSI * deltaTime,0));
    }

    if(keyCodes[GLFW_KEY_Q]){
        camera->rotate(Math::Quaternion::Euler(0,0,CAM_SENSI * deltaTime));
    }

    if(keyCodes[GLFW_KEY_E]){
        camera->rotate(Math::Quaternion::Euler(0,0,-CAM_SENSI * deltaTime));
    }
}