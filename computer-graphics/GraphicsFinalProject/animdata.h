#ifndef BONE_INFO_H
#define BONE_INFO_H

#include<glm/glm.hpp>

struct BoneInfo
{
	/*id is index in finalBoneMatrices*/
	int id;

	/*offset matrix transforms vertex from model space to bone space*/
	glm::mat4 offset;

};


#endif // !BONE_INFO_H
