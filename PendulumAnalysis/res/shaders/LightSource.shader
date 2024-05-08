#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}

#shader fragment
#version 330 core
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture, texCoord);
    fragColor = texColor;
}
