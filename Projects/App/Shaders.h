#pragma once
#include <string>
#include <sstream>
#include <fstream>


struct shaderSource{
    std::string vertex;
    std::string fragment;
};

shaderSource parseShaders(const std::string& filepath){
    std::ifstream stream(filepath);

    enum class shaderType{
        NONE=-1, VERTEX=0, FRAGMENT=1
    };
    std::string line;
    std::stringstream ss[2];
    shaderType type=shaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader")!=std::string::npos){
            if(line.find("vertex")!=std::string::npos){
                type=shaderType::VERTEX;
            }else if(line.find("fragment")!=std::string::npos){
                type=shaderType::FRAGMENT;
            }
        }else{
            ss[(int)type]<<line<<"\n";
        }
    }
    return {ss[0].str(),ss[1].str()};
}