#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "scene/models/Robot.h"
#include "App.h"


int main(void)
{
    App app;
    app.init();
    app.loop();
    app.terminate();
}