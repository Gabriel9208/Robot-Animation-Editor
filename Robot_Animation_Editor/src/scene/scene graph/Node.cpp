#include "Node.h"

Node::Node(Node&& other) noexcept:
	children(std::move(other.children)),
	modelMatrix(other.modelMatrix),
	parentModelMatrix(other.parentModelMatrix),
	object(std::move(other.object))
{}

Node& Node::operator=(Node&& other) noexcept
{
	children = std::move(other.children);
	modelMatrix = other.modelMatrix;
	parentModelMatrix = other.parentModelMatrix;
	object = std::move(other.object);

	return *this;
}


void Node::addChildren(const std::vector<Node*>& _childern)
{
}

void Node::updateChildMatrix()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->parentModelMatrix = modelMatrix * children[i]->parentModelMatrix;
	}
}

void Node::translate(float x, float y, float z)
{
	glm::vec4 trans = glm::vec4(x, y, z, 1);
	glm::vec4 e1 = glm::vec4(1, 0, 0, 0);
	glm::vec4 e2 = glm::vec4(0, 1, 0, 0);
	glm::vec4 e3 = glm::vec4(0, 0, 1, 0);
	glm::mat4 transMat = glm::mat4(e1, e2, e3, trans);
	
	modelMatrix = transMat * modelMatrix;
}

void Node::rotate(int x, int y, int z, float angle)
{
	float radian = glm::radians(angle);
	
	glm::vec4 col1 = glm::vec4(cos(radian) + (1 - cos(radian)) * x * x, 
							(1 - cos(radian)) * y * x + sin(radian) * z, 
							(1 - cos(radian)) * z * x - sin(radian) * y, 0);

	glm::vec4 col2 = glm::vec4((1 - cos(radian)) * y * x - sin(radian) * z,
							cos(radian) + (1 - cos(radian)) * y * y,
							(1 - cos(radian)) * z * y + sin(radian) * x, 0);

	glm::vec4 col3 = glm::vec4((1 - cos(radian)) * z * x + sin(radian) * y,
							(1 - cos(radian)) * z * y - sin(radian) * x,
							cos(radian) + (1 - cos(radian)) * z * z, 0);

	glm::vec4 col4 = glm::vec4(0, 0, 0, 1);

	glm::mat4 rotateMat = glm::mat4(col1, col2, col3, col4);
	
	glm::vec3 translateCache(modelMatrix[0][3], modelMatrix[1][3], modelMatrix[2][3]);
	translate(-translateCache.x, -translateCache.y, -translateCache.z);
	
}
