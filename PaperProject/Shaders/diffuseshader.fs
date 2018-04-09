#version 450 core
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
out vec4 FragColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
// texture samplers
uniform sampler2D texture1;
void main()
{

    // vec3 lightColor=vec3(1.0,1.0,1.0);
    // vec3 lightPos=vec3(30.0,30.0,30.0);
    vec3 objectColor=vec3(1.0,1.0,1.0);

      // ambient
    float ambientStrength = 0.0;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
  //vec3 lightDir=normalize(vec3(1.0,1.0,1.0));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
   // vec4 obj= texture(texture1, TexCoord);
    //vec3 result = (ambient + diffuse) *vec3(obj.x,obj.y,obj.z);
    FragColor = vec4(diffuse,1.0);

}