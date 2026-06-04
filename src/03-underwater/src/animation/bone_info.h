#ifndef BONE_INFO_H
#define BONE_INFO_H

#include <glm/glm.hpp>

struct BoneInfo
{
	// index in finalBoneMatrices
	int id;
	// matrix transforms vertex from model space to bone space
	glm::mat4 offset;
};

#endif
