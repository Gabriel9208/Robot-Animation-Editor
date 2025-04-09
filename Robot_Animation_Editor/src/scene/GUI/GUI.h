#pragma once
#include "../scene/EditorScene.h"

#include <GLFW/glfw3.h>
#include <cstdlib>


class GUI
{
private:
	EditorScene* scene; // Point to the scene that GUI is currently binding with
	Robot* robot;
	Node* selectedNode;

	bool seperateMode;

	int partSelected;
	void startFrame();
	void mainPanel();
	void transformPanel(Node* node);
	void _render();

public:
	GUI(GLFWwindow* window, EditorScene* _scene);
	~GUI();

	void init(GLFWwindow* window, EditorScene* _scene);
	void bindScene(EditorScene* _scene);
	void render();
	void terminate();

	void report();
};

