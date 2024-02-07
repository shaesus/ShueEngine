#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 fragPos;
out vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(aPos, 1.0);
    fragPos = vec3(u_Model * vec4(aPos, 1.0));
    normal = aNormal;
}

#shader fragment
#version 330 core
in vec3 fragPos;
in vec3 normal;

out vec4 fragColor;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPos;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(u_LightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;

    vec3 result = (ambient + diffuse) * u_ObjectColor;
    fragColor = vec4(result, 1.0);
}
