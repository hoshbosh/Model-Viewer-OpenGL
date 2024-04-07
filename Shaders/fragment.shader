#shader fragment
#version 330 core
in vec3 Color;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightColor;
in vec3 lightPosition;
in vec3 viewPosition;
out vec4 FragColor;
float near=0.1;
float far=100.0;
float fcoef=2.0/log2(far+1.0);
float linearizeDepth(float depth){
   float z=depth*2.0-1.0;
   return (2.0* near * far)/(far+near-z*(far-near));
}
void main(){

   float depth=linearizeDepth(gl_FragCoord.z)/far;
   // PHONG SHADING
   // vec3 lightDir=normalize(lightPosition-FragPos);
   // vec3 norm=normalize(Normal);
   // vec3 viewDir=normalize(viewPosition-FragPos);
   // vec3 reflectDir=reflect(-lightDir, norm);


   // float diff=max(dot(norm, lightDir),0.0);
   // vec3 diffuse=diff*lightColor;
   // // depth is for the z buffer demonstration
   // float specularStrength=0.0;
   // if(diff>0){
   //    specularStrength=0.75;
   // }
   // float spec=pow(max(dot(viewDir, reflectDir), 0.0),8);
   // vec3 specular=specularStrength*spec*lightColor;

   // float ambientStrength=0.3;
   // vec3 ambient=ambientStrength*lightColor;

   // vec3 result=(ambient +diffuse)*Color+specular;
   // FragColor = vec4(result, 1.0);
   FragColor = vec4(Color, 1.0);
  
};