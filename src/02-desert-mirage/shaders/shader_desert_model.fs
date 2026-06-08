#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D diffuseTexture;
uniform float useDiffuseMap;
uniform vec3 baseColor;

struct Light {
    vec3 dir;
    vec3 color;
};

uniform Light light;

void main()
{
    vec3 color = baseColor;
    if (useDiffuseMap > 0.5) {
        color = texture(diffuseTexture, TexCoord).rgb;
    }

    vec3 normal = normalize(Normal);
    vec3 ambient = 0.3 * light.color * color;
    float diff = max(dot(normal, normalize(-light.dir)), 0.0);
    vec3 diffuse = diff * light.color * color;

    FragColor = vec4(ambient + diffuse, 1.0);
}
