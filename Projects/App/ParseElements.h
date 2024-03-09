#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include "Vertex.h"
// struct elementData{
//     std::vector<unsigned int> i;
//     std::vector<float> v;
// };
Vertex token(std::string l){
    std::stringstream ss(l);
    std::string word;
    std::vector<float> temp;
    while(ss>>word){
        if(word!="v"){
        temp.push_back(std::stof(word));
        }
    }
    Vertex newVert=Vertex(glm::vec3{temp[0],temp[1], temp[2]});
    return newVert;
}
void tokenize(std::string l, std::vector<unsigned int>* i, char del){
    std::stringstream ss(l);
    std::string word;
    if(l!="f"){
        getline(ss, word, del);    
        i->push_back(std::stof(word)-1);
    }
}
