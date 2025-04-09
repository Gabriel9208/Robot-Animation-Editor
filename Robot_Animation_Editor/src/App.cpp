#include "App.h"
#include <GL/glew.h>

#include "scene/GUI/GUI.h"

int App::windowWidth = 800;
int App::windowHeight = 800;

static void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    Camara* camara = &(app->getCamara());
    glm::vec3 camaraPos = camara->getPos();
    glm::vec3 camaraTarget = camara->getTarget();
    const float OFFSET = 0.3f;

    if (action == GLFW_REPEAT || action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_W) // camara forward
        {
            camaraPos[2] -= OFFSET;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1], camaraTarget[2] - OFFSET));
            }
        }
        if (key == GLFW_KEY_S) // camara backward
        {
            camaraPos[2] += OFFSET;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1], camaraTarget[2] + OFFSET));
            }
        }
        if (key == GLFW_KEY_D) // camara go right
        {
            camaraPos[0] += OFFSET;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0] + OFFSET, camaraTarget[1], camaraTarget[2]));
            }
        }
        if (key == GLFW_KEY_A) // camara go left
        {
            camaraPos[0] -= OFFSET;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0] - OFFSET, camaraTarget[1], camaraTarget[2]));
            }
        }
        if (key == GLFW_KEY_E) // camara go up
        {
            camaraPos[1] += OFFSET;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1] + OFFSET, camaraTarget[2]));
            }
        }
        if (key == GLFW_KEY_Q) // camara go down
        {
            camaraPos[1] -= OFFSET;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1] - OFFSET, camaraTarget[2]));
            }
        }
    }
}

static void windowResize(GLFWwindow* window, int width, int height)
{
    App::setWindowHeight(height);
    App::setWindowWidth(width);
}

void App::glInit()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
}

App::~App()
{
    free(mainScene); 
    free(guiPanel); 
    free(window);
}

void App::init()
{
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 2); // smooth

    window = glfwCreateWindow(App::getWindowWidth(), App::getWindowHeight(), "Group6", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error";
    }

    glInit();

    mainScene = new EditorScene();
    guiPanel = new GUI(window, mainScene);
    glfwSetKeyCallback(window, keyPress);
    glfwSetFramebufferSizeCallback(window, windowResize);
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


