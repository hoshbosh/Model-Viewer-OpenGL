#shader vertex
#version 330 core
layout (location =0) in vec3 aPos;
layout (location =1) in vec3 color;
out vec3 Color;
void main(){
    Color=color;
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1000.0f);
};
#shader fragment
#version 330 core
in vec3 Color;
out vec4 FragColor;
void main(){
//    FragColor = vec4(0.0f,1.0f,0.0f, 1.0f);
   FragColor = vec4(Color, 1.0f);
};