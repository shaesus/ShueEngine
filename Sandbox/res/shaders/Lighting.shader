#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(aPos, 1.0);
    fragPos = vec3(u_Model * vec4(aPos, 1.0));
    normal = aNormal;
    texCoord = aTexCoord;
}

#shader fragment
#version 330 core
in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

struct Material 
{
    sampler2D diffuseMap;
    vec3 specular;
    float shininess;
};

uniform Material u_Material;

struct Light 
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light u_Light;

uniform vec3 u_ViewPos;
uniform sampler2D u_Texture;

void main()
{
    vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuseMap, texCoord));

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_Light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuseMap, texCoord));

    vec3 viewDir = normalize(u_ViewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    vec3 specular = u_Light.specular * (spec * u_Material.specular); 

    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}
