#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}

#shader fragment
#version 330 core
in vec2 texCoord;

out vec4 fragColor;

struct Material 
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

uniform Material u_Material;

void main()
{
    vec4 texColor = texture(u_Material.texture_diffuse1, texCoord);
    fragColor = texColor;
}
