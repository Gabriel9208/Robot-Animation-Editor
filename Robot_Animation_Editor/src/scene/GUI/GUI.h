#pragma once
#include <GLFW/glfw3.h>


class GUI
{
private:
	int partSelected;
	void startFrame();
	void defineInterface();
	void _render();
public:
	GUI() : partSelected(0) {}
	~GUI(){}

	void init(GLFWwindow* window);
	void render();
};

