#pragma once
#include "../scene/EditorScene.h"

#include <GLFW/glfw3.h>


class GUI
{
private:
	EditorScene* scene; // Point to the scene that GUI is currently binding with

	int partSelected;
	void startFrame();
	void defineInterface();
	void _render();

public:
	GUI(GLFWwindow* window, EditorScene* _scene);
	~GUI(){}

	void init(GLFWwindow* window, EditorScene* _scene);
	void bindScene(EditorScene* _scene);
	void render();
	void terminate();
};

