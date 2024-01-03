#version 330 core
out vec4 FragColor;

in vec3 crntPos;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

uniform vec4 lightColor;
uniform vec3 lighPos;
uniform vec3 camPos;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);
}