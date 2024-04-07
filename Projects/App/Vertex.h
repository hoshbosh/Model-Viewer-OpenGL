#pragma once
#include <vector>
#include <glm.hpp>
class Vertex{
    public:
    Vertex(glm::vec3 _pos);
    std::vector<float> getVertex();
    void setColor(glm::vec3 _col);
    void setNormal(glm::vec3 _norm){normal=_norm;};
    void setPosition(glm::vec4 newPos){position=newPos;};
    // GPU sided code below
    // void setPosition(glm::vec3 newPos){position=newPos;};
    glm::vec4 position;
    // GPU sided code below
    // glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
};