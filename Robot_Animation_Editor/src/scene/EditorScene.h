#pragma once
#include "./models/Robot.h"
#include "./camara/Camara.h"
#include "../graphics/shaders/ShaderProgram.h"
#include "./GUI/GUI.h"

#include <GLFW/glfw3.h>


class EditorScene
{
private:
	Robot robot;
	Camara camara;
	ShaderProgram program;

public:
	EditorScene();
	~EditorScene() {}

	void render();
};

