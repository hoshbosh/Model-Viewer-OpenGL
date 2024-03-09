#shader vertex
#version 330 core
layout (location =0) in vec3 aPos;
layout (location =1) in vec3 color;
out vec3 Color;
uniform mat4 trans;
void main(){
    Color=color;
   gl_Position = trans*vec4(aPos.x, aPos.y, aPos.z, 1000.0f);
};
