#shader vertex
#version 330 core
layout (location =0) in vec4 aPos;
layout (location =1) in vec3 color;
layout (location =2) in vec3 normal;
out vec3 Color;
out vec3 Normal;
out vec3 FragPos;
// GPU side transformation below
uniform mat4 trans;
void main(){
    // Color=color;
    Color=vec3(1.0, 0.0,0.0);

    Normal=normal;
//    gl_Position =vec4(aPos.x, aPos.y, aPos.z,aPos.w);
   gl_Position =trans* vec4(aPos.x, aPos.y, aPos.z,aPos.w);
   FragPos=vec3(aPos.x, aPos.y, aPos.z);
//    gl
    // GPU side transformation below
    //    gl_Position = trans*vec4(aPos.x, aPos.y, aPos.z,aPos.w);
};
