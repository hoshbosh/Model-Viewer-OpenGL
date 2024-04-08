#include "Object.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
std::vector<unsigned int> Object::getIndices(){
    // Temp is the array of vertices to be returned
    std::vector<unsigned int> temp;
    for(auto currTri:triangles){
        for(auto c: currTri.indices)
            temp.push_back(c); 
    }
    return temp;
}
Object::Object(std::string s){
    shadingType=false;
    std::string line;
    std::ifstream stream(s);
    int cont=0;
    trans=glm::mat4(1.0f);
    viewTrans=glm::mat4(1.0f);
    int normalIndexCont=0;
    std::vector<glm::vec3> normals;
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
                if(lineIndicies.size()==4){
                std::vector<unsigned int> temp;
                temp.push_back(lineIndicies[0]);
                temp.push_back(lineIndicies[1]);
                temp.push_back(lineIndicies[3]);
                triangles.push_back({temp});
                temp.clear();
                temp.push_back(lineIndicies[3]);
                temp.push_back(lineIndicies[1]);
                temp.push_back(lineIndicies[2]);
                triangles.push_back({temp});
                }else if(lineIndicies.size()==5){
                    std::cout<<"FUCCKKK"<<std::endl;
                }else{
                triangles.push_back({lineIndicies});
                }
            }
        }else if(line.find("vn ")!=std::string::npos){
            std::stringstream ss(line);
            std::string word;
            std::vector<float> temp;
            while(ss>>word){
                if(word!="vn"){
                    temp.push_back(std::stof(word));
                }
            }
            normals.push_back(glm::vec3{temp[0],temp[1], temp[2]});
        }
    }
    for(int i=0;i<normals.size();i++){
        vertices[i].setNormal(normals[i]);
    }

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
void Object::rotate(glm::vec3 axis){
    trans=glm::rotate(trans, glm::radians(0.1f), axis);
}
void Object::translate(glm::vec3 d){
    trans=glm::translate(trans, d);
}
void Object::scale(glm::vec3 s){
    trans=glm::scale(trans, s);
}
