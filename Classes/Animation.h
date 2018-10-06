#pragma once

#include <glm\glm.hpp>

struct Joint {
	glm::mat4x3 m_invBindPose; // inverse bind pose | transform
	const char* name;
	unsigned int m_iParent; // parent index or 0xFF | if root
};

struct Skeleton {
	unsigned int m_jointCount; // number of joints
	Joint* m_aJoint; // array of joints
};