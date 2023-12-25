#include <stb/stb_image.h>
#include<glad/glad.h>
#include "shaderClass.h"
#include "camera.h"
#include"Mesh.h"
#include "loadTexture.h"

using namespace std;

class Wall {
public:
	Shader* shader;
	unsigned int WallVAO, WallVBO, wallTexture;

	Wall(Shader& shader) {
		setupWall();
	}

	void setupWall() {
		float planeVertices[] = {
			// positions            // normals         // texcoords
			 10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
			-10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
			 10.0f, 0.0f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
			-10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
			 10.0f, 0.0f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
		};
	}

	void Draw(Shader& shader, Camera& camera, glm::mat4 projection) {
		//glm::mat4 model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		wallMesh.Draw(shader, camera);
	}


	Mesh GetMesh() {
		return wallMesh;
	}
private:
	Mesh wallMesh;
};