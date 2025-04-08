#include "App.h"
#include <GL/glew.h>

#include "scene/GUI/GUI.h"

void App::glInit()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
}

void App::init()
{
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 2); // smooth


    int windowWidth = 400;
    int windowHeight = 800;
    float aspectRatio = (float)windowWidth / windowHeight;

    window = glfwCreateWindow(windowWidth, windowHeight, "Group6", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error";
    }

    glInit();

    mainScene = new EditorScene();
    guiPanel = new GUI(window, mainScene);
    //glfwSetKeyCallback(window, keyPress);
}

void App::loop()
{
    while (!glfwWindowShouldClose(window))
    {
        mainScene->render();

        guiPanel->render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

void App::terminate()
{
    guiPanel->terminate();
    glfwTerminate();
}
