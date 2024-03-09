#shader vertex
#version 330 core
layout (location =0) in vec4 aPos;
layout (location =1) in vec3 color;
out vec3 Color;
// GPU side transformation below
// uniform mat4 trans;
void main(){
    Color=color;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z,aPos.w);
    // GPU side transformation below
    //    gl_Position = trans*vec4(aPos.x, aPos.y, aPos.z,aPos.w);
};
