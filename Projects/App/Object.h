#pragma once
#include <glm.hpp>
#include <vector>
#include "Vertex.h"
#include <string>
class Object{
    public:
    Object(std::string s);
    std::vector<float> getVBO();
    std::vector<unsigned int> getIndices(){return indicies;};
    void rotate(float theta);
    glm::mat4 trans;
    private:
    int size;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indicies;
};