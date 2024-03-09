#include <GLFW/glfw3.h>
#include "Object.h"
#include <iostream>
void processInput(GLFWwindow *window, Object* obj, float theta)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        // obj->rotate(theta);
    }
}