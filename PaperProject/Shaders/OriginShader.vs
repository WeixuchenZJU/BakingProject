#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec2 aBC;

out VS_OUT
{
   // texture samplers
    vec2 TexCoords;
    vec3 FragPos;
    vec3 Normal;
    vec2 BC;
} vs_out;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
    vs_out.BC=aBC;
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;  
    gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
    vs_out.TexCoords=aTexCoords;
//Compute on Vertex
   //vec4 obj_diffuse=texture(texture1,aTexCoords);
  //  VertexColor=vec3(obj_diffuse.x,obj_diffuse.y,obj_diffuse.z);
}