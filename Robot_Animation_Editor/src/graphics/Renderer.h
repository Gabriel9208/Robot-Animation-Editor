#pragma once
#include "vertex/EBO.h"
#include "vertex/VAO.h"
#include "shaders/ShaderProgram.h"
#include "../scene/models/Object.h"
#include "../scene/camara/Camara.h"
#include "../scene/scene graph/Node.h"


class Renderer
{
private:
	Renderer() {}
	~Renderer() {}

	static Renderer instance;
public:
	static Renderer& getInstance();

	void drawElement(const ShaderProgram& program, Node& vode, const Camara& camara) const;
	void clear();
};