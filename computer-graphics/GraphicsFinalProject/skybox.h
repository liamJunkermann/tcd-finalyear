#ifndef SKYBOX_CLASS_H
#define SKYBOX_CLASS_H

#include"shaderClass.h"
#include"camera.h"
#include"VAO.h"
#include"VBO.h"
#include<vector>

using namespace std;
class Skybox
{
public:
	Skybox(Shader& shader, vector<string> faces, float vertices[]);
	//Shader skyShader;
	//VBO VBO;
	VAO VAO;

	void Draw(Shader& shader, Camera& camera, glm::mat4 projection);
	static unsigned int LoadCubemap(vector<string> faces);
private:
	unsigned int cubeTexture;
	unsigned int cubemapTexture;

};
#endif // !SKYBOX_CLASS_H
