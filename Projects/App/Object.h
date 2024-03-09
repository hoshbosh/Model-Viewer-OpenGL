#pragma once
#include <glm.hpp>
#include <vector>
#include "Vertex.h"
#include <string>
struct Triangle{
    std::vector<unsigned int> indices;
};
class Object{
    public:
    Object(std::string s);
    std::vector<float> getVBO();
    std::vector<unsigned int> getIndices();
    void rotate(float theta, glm::vec3 axis);
    void translate(glm::vec3 d);
    void scale(glm::vec3 s);
    glm::mat4 trans;
    private:
    int size;
    std::vector<Vertex> vertices;
    std::vector<Triangle> triangles;
};