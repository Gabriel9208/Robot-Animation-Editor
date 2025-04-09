#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "../models/Object.h"


class Node
{
private:
	std::vector<Node*> children;

	bool dirty;

	glm::quat rotateOffset;
	glm::vec3 translateOffset;

	glm::mat4 modelMatrix; // Transformation matrix of itself
	glm::mat4 parentModelMatrix; // Transformation matrix of itself

	Object object;


public:
	Node(const std::string& modelPath,
		const std::string& mtlPath,
		const std::string& filePrefix = "res/robot/",
		std::vector<Node*> _childern = {});

	Node(const Node& other) = delete;
	Node(Node&& other) noexcept;

	~Node() {}

	Node& operator=(const Node& other) = delete;
	Node& operator=(Node&& other) noexcept;


	void addChildren(const std::vector<Node*>& _childern);
	void updateChildMatrix();

	void setTranslate(glm::vec3 trans);
	void setRotate(glm::vec3 eular);
	void updateModelMatrix();


	inline bool isDirty() { return dirty; }
	inline Object& getObject() { return object; }
	inline glm::mat4 getModelMatrix() const { return modelMatrix; }
	inline glm::mat4 getParentModelMatrix() const { return parentModelMatrix; }
	inline glm::vec3 getTranslateOffset() const { return translateOffset; }
	inline glm::vec3 getRotateAngle() const { return glm::degrees(glm::eulerAngles(rotateOffset)); }
};

