#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));
	Normal = aNormal;
	texCoords = aTex;

	gl_Position = projection * view * vec4(crntPos, 1.0);
}