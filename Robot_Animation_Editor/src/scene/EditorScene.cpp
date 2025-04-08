#include "EditorScene.h"
#include "../graphics/Renderer.h"


EditorScene::EditorScene() :
    camara(),
    program(),
    robot()
{
    program.createShader(GL_VERTEX_SHADER, "res/shaders/vertex_shader.glsl");
    program.createShader(GL_FRAGMENT_SHADER, "res/shaders/fragment_shader.glsl");
}

void EditorScene::render()
{
    Renderer& renderer = Renderer::getInstance();
    robot.render(renderer, camara, program);
}
