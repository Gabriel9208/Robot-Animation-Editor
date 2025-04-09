#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camara
{
private:
	glm::vec3 pos;
	glm::vec3 target;
	glm::vec3 up;

	glm::mat4 lookAtMat;

	void genLookAt();

public:
	Camara();
	Camara(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 upVector);
	~Camara() {}

	void setPos(glm::vec3 newPos);
	void setTarget(glm::vec3 newTarget);
	void setUpVector(glm::vec3 newUp);

	inline glm::vec3 getPos() const { return pos; }
	inline glm::mat4 lookAt() const { return glm::lookAt(pos, target, up); }
};