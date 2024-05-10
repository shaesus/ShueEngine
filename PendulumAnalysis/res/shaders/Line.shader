#shader vertex
#version 330 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
    gl_Position = u_Proj * u_View * u_Model * vec4(a_Position, 1.0);
};

#shader fragment
#version 330 core

out vec4 color;

uniform vec4 u_Color;

void main()
{
    color = u_Color;
};
