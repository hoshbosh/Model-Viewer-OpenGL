#include "Vertex.h"

Vertex::Vertex(glm::vec3 _pos){
    position=glm::vec4{_pos.x, _pos.y, _pos.z, 1000.0f};
    // GPU code below
    // position=glm::vec3{_pos.x, _pos.y, _pos.z};
}
void Vertex::setColor(glm::vec3 _col){
    color=_col;
}
std::vector<float> Vertex::getVertex(){
    std::vector<float> combined;
    combined.push_back(position.x);
    combined.push_back(position.y);
    combined.push_back(position.z);
    combined.push_back(position.w);
    combined.push_back(color.x);
    combined.push_back(color.y);
    combined.push_back(color.z);
   return combined;
}