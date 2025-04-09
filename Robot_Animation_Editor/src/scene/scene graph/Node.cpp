#include "Node.h"

Node::Node(const std::string& modelPath,
	const std::string& mtlPath,
	const std::string& filePrefix,
	std::vector<Node*> _childern) :

	object(modelPath, mtlPath, filePrefix),
	dirty(false),
	rotateOffset(1.0f, 0.0f, 0.0f, 0.0f),
	translateOffset(0.0f),
	modelMatrix(1.0f),
	parentModelMatrix(1.0f)
{
	addChildren(_childern);
	updateModelMatrix();
}

Node::Node(Node&& other) noexcept:
	object(std::move(other.object)),
	dirty(false),
	rotateOffset(other.rotateOffset),
	translateOffset(other.translateOffset),
	children(std::move(other.children)),
	modelMatrix(other.modelMatrix),
	parentModelMatrix(other.parentModelMatrix)
{}

Node& Node::operator=(Node&& other) noexcept
{
	children = std::move(other.children);
	modelMatrix = other.modelMatrix;
	parentModelMatrix = other.parentModelMatrix;
	object = std::move(other.object);

	return *this;
}

void Node::updateModelMatrix()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), translateOffset) * glm::mat4_cast(rotateOffset);
	updateChildMatrix();
	dirty = false;
}

void Node::addChildren(const std::vector<Node*>& _childern)
{
	children.insert(children.end(), _childern.begin(), _childern.end());
}

void Node::updateChildMatrix()
{
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->parentModelMatrix = modelMatrix;
	}
}

void Node::setTranslate(glm::vec3 trans)
{
	translateOffset = trans;
	dirty = true;
}

void Node::setRotate(glm::vec3 eular)
{
	if (eular == getRotateAngle())
	{
		return;
	}

	glm::vec3 eularAngle = glm::radians(eular);
	rotateOffset = glm::quat(eularAngle);

	rotateOffset = glm::normalize(rotateOffset); 
	dirty = true;
}
