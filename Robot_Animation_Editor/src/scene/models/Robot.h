#pragma once

#include <vector>

#include "../graphics/Renderer.h"
#include "../camara/Camara.h"
#include "../graphics/shaders/ShaderProgram.h"
#include "../scene graph/Node.h"



class Robot
{
private:
	std::vector<Node> parts;

public:
	Robot();
	~Robot() {}

	void render(Renderer& renderer, const Camara& camara, const ShaderProgram& program);

	inline Node& getNode(unsigned int index) { return parts[index]; }
};

