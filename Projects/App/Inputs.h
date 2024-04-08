#include <GLFW/glfw3.h>
#include "Object.h"
#include <iostream>
void processInput(GLFWwindow *window, Object* obj, float theta)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        obj->rotate(glm::vec3{0.0f, 0.0f, 1.0f});
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        obj->rotate(glm::vec3{0.0f, 0.0f, -1.0f});
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        obj->rotate(glm::vec3{1.0f, 0.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        obj->rotate(glm::vec3{-1.0f, 0.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        obj->rotate(glm::vec3{0.0f, 1.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        obj->rotate(glm::vec3{0.0f, -1.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        obj->translate(glm::vec3{1.0f, 0.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        obj->translate(glm::vec3{-1.0f, 0.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        obj->translate(glm::vec3{0.0f, 1.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        obj->translate(glm::vec3{0.0f, -1.0f, 0.0f});
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        obj->translate(glm::vec3{0.0f, 0.0f, -0.01f});
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        obj->translate(glm::vec3{0.0f, 0.0f, 0.01f});
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        obj->scale(glm::vec3{0.9995f, 0.9995f, 0.9995f});
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        obj->scale(glm::vec3{1.005f, 1.005f, 1.005f});
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        obj->toggleShading();
}