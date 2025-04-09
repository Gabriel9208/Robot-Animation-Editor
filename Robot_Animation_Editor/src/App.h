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

	void glInit();
public:
	App(): window(nullptr), mainScene(nullptr), guiPanel(nullptr) {}
	~App();

	void init();
	void loop();
	void terminate();

	inline Camara& getCamara() { return mainScene->getCamara(); }
};

