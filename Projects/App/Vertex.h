#pragma once
#include <vector>
#include <glm.hpp>
class Vertex{
    public:
    Vertex(glm::vec3 _pos);
    std::vector<float> getVertex();
    void setColor(glm::vec3 _col);
    void setPosition(glm::vec3 newPos){position=newPos;};
    glm::vec3 position;
    glm::vec3 color;
};