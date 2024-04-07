#shader fragment
#version 330 core
in vec3 Color;
in float flogz;
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
   // depth is for the z buffer demonstration
   // FragColor = vec4(vec3(depth),1.0f);
   // Color is for the actual color
   FragColor = vec4(Color, 1.0f);
};