#pragma once
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../models/Object.h"

class Node
{
private:
	std::vector<Node*> children;

	glm::mat4 modelMatrix; // Transformation matrix of itself
	glm::mat4 parentModelMatrix; // Transformation matrix of itself

	Object object;

public:
	Node(const std::string& modelPath, 
		const std::string& mtlPath, 
		const std::string& filePrefix = "res/robot/",
		std::vector<Node*> _childern = {}) :
		modelMatrix(1.0f),
		parentModelMatrix(1.0f),
		object(modelPath, mtlPath, filePrefix)
	{}

	Node(const Node& other) = delete;
	Node(Node&& other) noexcept;

	~Node() {}

	Node& operator=(const Node& other) = delete;
	Node& operator=(Node&& other) noexcept;


	void addChildren(const std::vector<Node*>& _childern);
	void updateChildMatrix();

	void translate(float x, float y, float z);
	void rotate(int x, int y, int z, float angle);

	inline Object& getObject() { return object; }
};

