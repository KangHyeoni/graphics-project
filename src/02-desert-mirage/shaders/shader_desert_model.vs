#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aTangent;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoord = aTexCoord;
    FragPos = vec3(world * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(world))) * aNormal;
    gl_Position = projection * view * world * vec4(aPos, 1.0);
}
