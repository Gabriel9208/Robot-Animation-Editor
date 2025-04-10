#include "App.h"
#include <GL/glew.h>

#include "scene/GUI/GUI.h"

#include "glm/gtc/quaternion.hpp"
#include "imgui/imgui.h"             
#include "imgui/imgui_impl_glfw.h"

int App::windowWidth = 800;
int App::windowHeight = 800;

double lastCursorX;
double lastCursorY;

bool mouseMiddlePressed;
bool mouseRightPressed;


static void keyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    Camara* camara = &(app->getCamara());
    glm::vec3 camaraPos = camara->getPos();
    glm::vec3 camaraTarget = camara->getTarget();
    const float ROTATE_SPEED = 2.0f;
    const float TRANSLATE_SPEED = 0.5f;

    if (action == GLFW_REPEAT || action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_W) // camara forward
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camaraPos[2] -= TRANSLATE_SPEED;
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1], camaraTarget[2] - TRANSLATE_SPEED));
                camara->setPos(camaraPos);
            }
            else
            {
                camara->rotateAround(-ROTATE_SPEED, glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }
        if (key == GLFW_KEY_S) // camara backward
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camaraPos[2] += TRANSLATE_SPEED;
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1], camaraTarget[2] + TRANSLATE_SPEED));
                camara->setPos(camaraPos);
            }
            else
            {
                camara->rotateAround(ROTATE_SPEED, glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }
        if (key == GLFW_KEY_D) // camara go right
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camaraPos[0] += TRANSLATE_SPEED;
                camara->setTarget(glm::vec3(camaraTarget[0] + TRANSLATE_SPEED, camaraTarget[1], camaraTarget[2]));
                camara->setPos(camaraPos);
            }
            else
            {
                camara->rotateAround(ROTATE_SPEED, glm::vec3(0.0f, 1.0f, 0.0f));

            }
        }
        if (key == GLFW_KEY_A) // camara go left
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camaraPos[0] -= TRANSLATE_SPEED;
                camara->setTarget(glm::vec3(camaraTarget[0] - TRANSLATE_SPEED, camaraTarget[1], camaraTarget[2]));
                camara->setPos(camaraPos);
            }
            else
            {
                camara->rotateAround(-ROTATE_SPEED, glm::vec3(0.0f, 1.0f, 0.0f));

            }
        }
        if (key == GLFW_KEY_E) // camara go up
        {
            camaraPos[1] += TRANSLATE_SPEED;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1] + TRANSLATE_SPEED, camaraTarget[2]));
            }
        }
        if (key == GLFW_KEY_Q) // camara go down
        {
            camaraPos[1] -= TRANSLATE_SPEED;
            camara->setPos(camaraPos);
            if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) != GLFW_PRESS) {
                camara->setTarget(glm::vec3(camaraTarget[0], camaraTarget[1] - TRANSLATE_SPEED, camaraTarget[2]));
            }
        }
    }
}

static void windowResize(GLFWwindow* window, int width, int height)
{
    App::setWindowHeight(height);
    App::setWindowWidth(width);
}

static void mouseEvent(GLFWwindow* window, int button, int action, int mods)
{
    
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
    
    ImGuiIO& io = ImGui::GetIO();
    if (!io.WantCaptureMouse) {
        if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &lastCursorX, &lastCursorY);
            mouseMiddlePressed = true;

        }
        if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
        {
            mouseMiddlePressed = false;

        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        {
            glfwGetCursorPos(window, &lastCursorX, &lastCursorY);
            mouseRightPressed = true;
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        {
            mouseRightPressed = false;
        }
    }
}

static void cursorEvent(GLFWwindow* window, double xpos, double ypos)
{
    if (mouseMiddlePressed || mouseRightPressed)
    {
        App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
        Camara* camara = &(app->getCamara());
        glm::vec3 camaraPos = camara->getPos();
        glm::vec3 camaraTarget = camara->getTarget();
    
        double x = xpos - lastCursorX;
        double y = ypos - lastCursorY;
    
        float translationSpeedFactor = 0.125f;
        float rotationSpeedFactor = 0.75f;
    
        if (mouseMiddlePressed)
        {
            camara->rotateAround(-y * rotationSpeedFactor, glm::vec3(1.0f, 0.0f, 0.0f));
            camara->rotateAround(-x * rotationSpeedFactor, glm::vec3(0.0f, 1.0f, 0.0f));
        }
    
        if (mouseRightPressed)
        {
            camaraPos[0] += -x * translationSpeedFactor;
            camaraPos[1] += y * translationSpeedFactor;
    
            camara->setTarget(glm::vec3(camaraTarget[0] - x * translationSpeedFactor, camaraTarget[1] + y * translationSpeedFactor, camaraTarget[2]));
            camara->setPos(camaraPos);
        }
    
        lastCursorX = xpos;
        lastCursorY = ypos;
    }
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

    mouseMiddlePressed = false;
    mouseRightPressed = false;

    mainScene = new EditorScene();
    guiPanel = new GUI(window, mainScene);
    glfwSetKeyCallback(window, keyPress);
    glfwSetFramebufferSizeCallback(window, windowResize);
    glfwSetMouseButtonCallback(window, mouseEvent);
    glfwSetCursorPosCallback(window, cursorEvent);
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


