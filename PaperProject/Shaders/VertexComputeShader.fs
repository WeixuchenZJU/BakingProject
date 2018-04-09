#version 450 core
//in vec3 VertexColor;
in VS_OUT
{
   // texture samplers
    vec2 TexCoords;
    vec3 FragPos;
    vec3 Normal;
    vec2 BC;
} fs_in;
out vec4 FragColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D texture1;
void main()
{
   //vec3 lightdir=(lightPos-FragPos);
  //  float dis=length(lightdir);
    //lightdir=normalize(lightdir);
    //float cosineterm=max(0.0,dot(lightdir,Normal));
   // vec3 light=cosineterm*lightColor;
   //FragColor=vec4(light,1.0f);
   // vec4 objcolor=texture(texture1,TexCoords);
   // vec3 result=vec3(objcolor.x,objcolor.y,objcolor.z)*light;
    //FragColor=vec4(light,1.0);
  //  FragColor = vec4(VertexColor,1.0);
vec3 cp0=vec3(1.0,0.0,0.0);
vec3 cp1=vec3(0.0,1.0,0.0);
vec3 cp2=vec3(0.0,0.0,1.0);

vec3 cp01=vec3(1.0,1.0,0.0);
vec3 cp12=vec3(0.0,1.0,1.0);
vec3 cp02=vec3(1.0,0.0,1.0);
  float s=fs_in.BC.x;
  float t=fs_in.BC.y;
  float u=1-s-t;
  float B200=s*s;
  float B110=2*s*t;
  float B101=2*s*u;
  float B020=t*t;
  float B011=2*t*u;
  float B002=u*u;
  vec3 res=B200*cp0+B110*cp01+B101*cp02+B020*cp1+B011*cp12+B002*cp2;
  FragColor=vec4(res,1.0);
 // FragColor=texture(texture1,fs_in.TexCoords);
 // FragColor=vec4(fs_in.BC.x,fs_in.BC.y,1-fs_in.BC.x-fs_in.BC.y,1.0);
}