#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 fragColor;

void main()
{
    fragColor = vec4(1.0); // set all 4 vector values to 1.0
}
