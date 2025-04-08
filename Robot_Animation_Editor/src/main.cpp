#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "scene/models/Robot.h"
#include "scene/camara/Camara.h"
#include "graphics/shaders/ShaderProgram.h"
#include "graphics/Renderer.h"
#include "scene/GUI/GUI.h"

void GLInit()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
}

void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

int main(void)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 2); // smooth


    int windowWidth = 400;
    int windowHeight = 800;
    float aspectRatio = (float)windowWidth / windowHeight;

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Group6", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error";
    }

    GLInit();

    GUI imgui;
    imgui.init(window);

    Camara camara;
    Renderer& renderer = Renderer::getInstance();
    ShaderProgram program;

    program.createShader(GL_VERTEX_SHADER, "res/shaders/vertex_shader.glsl");
    program.createShader(GL_FRAGMENT_SHADER, "res/shaders/fragment_shader.glsl");

    Robot robot;
    
    glfwSetKeyCallback(window, keyPress);

    while (!glfwWindowShouldClose(window))
    {
        robot.render(renderer, camara, program);

        imgui.render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}