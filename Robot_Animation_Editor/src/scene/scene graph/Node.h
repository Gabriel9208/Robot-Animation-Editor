#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../models/Object.h"

class Node
{
private:
	std::vector<Node*> children;

	glm::mat4 transformMatrix; // Transformation matrix of itself
	glm::mat4 parentTransformMatrix; // Transformation matrix of itself

	Object object;

public:
	Node(std::vector<Node> _childern, 
		const std::string& modelPath, 
		const std::string& mtlPath, 
		const std::string& filePrefix = "res/robot/"): 
		transformMatrix(0.0f),
		parentTransformMatrix(1.0f),
		object(modelPath, mtlPath, filePrefix)
	{}

	~Node() {}

	void updateChildMatrix();

	void translate(float x, float y, float z);
	void rotate(int axis, float angle);

};

