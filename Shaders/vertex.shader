#shader vertex
#version 330 core
layout (location =0) in vec4 aPos;
layout (location =1) in vec3 color;
layout (location =2) in vec3 normal;
out vec3 Color;
out vec3 Normal;
out vec3 FragPos;
out vec3 lightColor;
out vec3 lightPosition;
out vec3 viewPosition;
// GPU side transformation below
uniform mat4 trans;
uniform bool shading;
void main(){
   gl_Position =trans* vec4(aPos.x, aPos.y, aPos.z,aPos.w);
   FragPos=vec3(aPos.x, aPos.y, aPos.z);
    Normal=normal;

   lightColor=vec3(1.0,1.0,1.0);
   lightPosition=vec3(5.0,0.0,-5.0);
   viewPosition=vec3(0.0,0.0,0.0);
   vec3 tempColor=vec3(1.0, 0.0,0.0);
   if(shading){
    Color=vec3(1.0, 0.0,0.0);
   }else{

   // vec3 tempColor=color;
   //  Color=color;

//    gl_Position =vec4(aPos.x, aPos.y, aPos.z,aPos.w);
   vec3 position=vec3(aPos.x, aPos.y, aPos.z);
   vec3 lightDir=normalize(lightPosition-position);
   vec3 norm=normalize(normal);
   vec3 viewDir=normalize(viewPosition-position);
   vec3 reflectDir=reflect(-lightDir, norm);


   float diff=max(dot(norm, lightDir),0.0);
   vec3 diffuse=diff*lightColor;
   // depth is for the z buffer demonstration
   float specularStrength=2.0;
   float spec=pow(max(-dot(viewDir, reflectDir), 0.0),32);
   if(diff==0.0){
      specularStrength=0.0;
   }
   vec3 specular=specularStrength*spec*lightColor;

   float ambientStrength=0.3;
   vec3 ambient=ambientStrength*lightColor;
   // // if(spec==0.0){
   // //  tempColor=vec3(0.0,0.0,1.0);
   // // }
   Color =(specular+ambient+diffuse)*tempColor+specular;
//    gl
    // GPU side transformation below
    //    gl_Position = trans*vec4(aPos.x, aPos.y, aPos.z,aPos.w);
   }
};
