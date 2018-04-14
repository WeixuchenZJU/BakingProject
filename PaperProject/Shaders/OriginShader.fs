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
   //Light dir
   vec3 Lightdir=normalize(lightPos-fs_in.FragPos);
   vec4 diffusetexture4=texture(texture1,fs_in.TexCoords);
   vec3 diffusetexture3=vec3(diffusetexture4.x,diffusetexture4.y,diffusetexture4.z);
   vec3 light=max(0.0,dot(fs_in.Normal,Lightdir))*lightColor;
   FragColor=vec4(light,1.0);
   //FragColor=vec4(light*diffusetexture3,1.0);
}