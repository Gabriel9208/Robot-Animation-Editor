#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"


class Camara
{
private:
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 lookAtMat;

	void genLookAt();
	void updateVectors(const glm::quat deltaOrientation);

public:
	Camara();
	Camara(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 upVector);
	~Camara() {}

	void setPos(glm::vec3 newPos);
	void setTarget(glm::vec3 newTarget);
	void setUpVector(glm::vec3 newUp);

	void rotateAround(float angle, glm::vec3 axis);

	inline glm::vec3 getPos() const { return pos; }
	inline glm::vec3 getTarget() const { return target; }

	inline glm::mat4 lookAt() const { return glm::lookAt(pos, target, up); }
};