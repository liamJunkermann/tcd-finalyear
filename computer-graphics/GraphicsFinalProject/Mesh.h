#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>
#include"VAO.h"
#include"EBO.h"
#include"camera.h"

using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;  // we store the path of the texture to compare with other textures
};


class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture>      textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	Mesh();

	void Draw(
		Shader& shader,
		Camera& camera
		//glm::mat4 model = glm::mat4(1.0f),
		//glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)1000 / (float)1000, 0.1f, 100.0f)
	);
private:
	// render data 
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
};

#endif // !MESH_CLASS_H
