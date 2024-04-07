#shader fragment
#version 330 core
in vec3 Color;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
float near=0.1;
float far=100.0;
float fcoef=2.0/log2(far+1.0);
float linearizeDepth(float depth){
   float z=depth*2.0-1.0;
   return (2.0* near * far)/(far+near-z*(far-near));
}
void main(){
   vec3 lightColor=vec3(1.0,1.0,1.0);
   float depth=linearizeDepth(gl_FragCoord.z)/far;
   vec3 lightPosition=vec3(0.0,0.0,0.0);
   vec3 viewPosition=vec3(0.0,0.0,0.0);
   vec3 lightDir=normalize(lightPosition-FragPos);
   vec3 norm=normalize(Normal);
   float specularStrength=0.5;
   vec3 viewDir=normalize(viewPosition-FragPos);
   vec3 reflectDir=reflect(-lightDir, norm);
   float spec=pow(max(dot(viewDir, reflectDir), 0.0),32);
   vec3 specular=specularStrength*spec*lightColor;
   float diff=max(dot(norm, lightDir),0.0);
   // depth is for the z buffer demonstration

   // FragColor = vec4(vec3(depth),1.0f);
   // Color is for the actual color
   float ambientStrength=0.1;
   vec3 diffuse=diff*lightColor;
   vec3 ambient=ambientStrength*lightColor;
   vec3 result=(ambient+diffuse+specular)*Color;
   FragColor = vec4(result, 1.0);
};