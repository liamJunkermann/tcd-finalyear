#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glm/glm.hpp>
#include<glad/glad.h>
#include<vector>

struct BaseVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texUV;
};

class VBO
{
public:
	GLuint ID;
	VBO(std::vector<BaseVertex>& vertices);
	VBO(std::vector<glm::vec3>& vertices);
	VBO(float vertices[]);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
