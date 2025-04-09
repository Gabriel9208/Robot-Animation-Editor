#pragma once
#include "./scene/EditorScene.h"
#include "./scene/GUI/GUI.h"

#include <cstdlib>
#include "scene/camara/Camara.h"


class App
{
private: 
	GLFWwindow* window;
	EditorScene* mainScene;
	GUI* guiPanel;

	static int windowWidth;
	static int windowHeight;

	void glInit();
public:
	App(): window(nullptr), mainScene(nullptr), guiPanel(nullptr) {}
	~App();

	void init();
	void loop();
	void terminate();

	static void setWindowWidth(int w) { windowWidth = w; }
	static void setWindowHeight(int h) { windowHeight = h; }
	static int getWindowWidth() { return windowWidth; }
	static int getWindowHeight() { return windowHeight; }
	inline Camara& getCamara() { return mainScene->getCamara(); }
};

