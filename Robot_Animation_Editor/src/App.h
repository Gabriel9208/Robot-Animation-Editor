#pragma once
#include "./scene/EditorScene.h"
#include "./scene/GUI/GUI.h"

class App
{
private: 
	GLFWwindow* window;
	EditorScene mainScene;
	GUI guiPanel;

	void glInit();
public:
	App() {}
	~App() {}

	void init();
	void loop();
	void terminate();
};

