#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include<vector>
#include<glm/glm.hpp>

#include"shaderClass.h"
#include"camera.h"
#include"VAO.h"
#include"VBO.h"
#include <stb/stb_image.h>

using namespace std;
//unsigned int loadTexture(char const* path);

class Cube {
public:
	VAO VAO;
	unsigned int cubemapTexture;
	Cube(unsigned int cubemapTexture);

	void Draw(Shader& shader, Camera& camera, glm::mat4 projection);
};

#endif