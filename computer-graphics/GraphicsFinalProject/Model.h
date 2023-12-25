#ifndef CLASS_MODEL_H
#define CLASS_MODEL_H

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
#include<stb/stb_image.h>
#include <map>

#include"shaderClass.h"
#include"camera.h"
#include"Mesh.h"
#include "animdata.h"
#include "assimpglmhelpers.h"

using namespace std;


class Model {
public:
	Model(char* path);
	void Draw(Shader& shader, Camera& camera);

	auto& GetBoneInfoMap() { return m_BoneInfoMap; };
	int& GetBoneCount() { return m_BoneCounter; };

	static unsigned int TextureFromFile(const char* path, const string& directory);
private:
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;

	std::map<string, BoneInfo> m_BoneInfoMap;
	int m_BoneCounter = 0;


	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	
	void SetVertexBoneDataToDefault(Vertex& vertex);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	void SetVertexBoneData(Vertex& vertex, int boneID, float weight);
	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices, aiMesh* mesh, const aiScene* scene);


	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		string typeName);



};

#endif // !CLASS_MODEL_H
