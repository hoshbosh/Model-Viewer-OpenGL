#include "Object.h"
// #include "ParseElements.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
Object::Object(std::string s){
    std::string line;
    std::ifstream stream(s);
    int cont=0;
    std::vector<glm::vec3> colors{
        glm::vec3{1.0f, 0.0f, 0.0f}, 
        glm::vec3{0.0f, 1.0f, 0.0f}, 
        glm::vec3{0.0f, 0.0f, 1.0f}, 
    };
    while(getline(stream, line)){
        if(line.find("v ")!=std::string::npos){
            std::stringstream ss(line);
            std::string word;
            std::vector<float> temp;
            while(ss>>word){
                if(word!="v"){
                temp.push_back(std::stof(word));
                }
            }
            Vertex tempVert=Vertex(glm::vec3{temp[0],temp[1], temp[2]});
            if(cont%3==0){
                tempVert.setColor(colors[0]);
            }
            if(cont%3==1){
                tempVert.setColor(colors[1]);
            }
            if(cont%3==2){
                tempVert.setColor(colors[2]);
            }
            cont++;
            vertices.push_back(tempVert);
        }else if(line.find("f ")!=std::string::npos){
            std::stringstream ss(line);
            std::string word;
            std::vector<unsigned int> lineIndicies;
            while(ss>>word){
                if(word!="f"){
                    if(line.find("//")!=std::string::npos){
                        // tokenize(word, &lineIndicies, '/');
                        std::stringstream sss(word);
                        std::string word;
                        if(word!="f"){
                            getline(sss, word, '/');    
                            lineIndicies.push_back(std::stof(word)-1);
                        }
                    }else{
                        lineIndicies.push_back(std::stof(word));
                    }
                }
                for(auto c: lineIndicies)
                    indicies.push_back(c);
            }
        }

    }

        // verticies.push_back(cont%3.0f)
}
std::vector<float> Object::getVBO(){
    std::vector<float> temp;
    for(auto curr: vertices){
        for(float attrib:curr.getVertex()){
            temp.push_back(attrib);
        }
    }
    return temp;
}
void Object::rotate(float theta){
    glm::mat4 trans;
    trans=glm::rotate(trans, glm::radians(45.0f), glm::vec3{-1.0f, 0.0f, 0.0f});
    for(auto  currentVert : vertices){
        currentVert.setPosition(trans*currentVert.position);
    }
}