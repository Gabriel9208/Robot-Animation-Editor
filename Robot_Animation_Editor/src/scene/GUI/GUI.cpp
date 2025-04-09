#include "GUI.h"

#include "glm/glm.hpp"
#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/string_cast.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#define HEAD 0
#define TOP_BODY 1
#define BOTTOM_BODY 2
#define RIGHT_UPPER_ARM 3
#define RIGHT_LOWER_ARM 4
#define RIGHT_HAND 5
#define LEFT_UPPER_ARM 6
#define LEFT_LOWER_ARM 7
#define LEFT_HAND 8
#define RIGHT_THIGH 9
#define RIGHT_CALF 10
#define RIGHT_FOOT 11
#define LEFT_THIGH 12
#define LEFT_CALF 13
#define LEFT_FOOT 14

GUI::GUI(GLFWwindow* window, EditorScene* _scene) : partSelected(0)
{
    init(window, _scene);
}

GUI::~GUI()
{
    free(robot);
    free(selectedNode);
    free(scene);
}

void GUI::init(GLFWwindow* window, EditorScene* _scene)
{
    const char* glsl_version = "#version 450";

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bindScene(_scene);
    robot = &(scene->getRobot());
    selectedNode = &(robot->getNode(HEAD));
}

void GUI::bindScene(EditorScene* _scene)
{
    if (_scene != nullptr)
    {
        scene = _scene;
    }
}

void GUI::render()
{
    startFrame();
    mainPanel();
    _render();
}

void GUI::terminate()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::startFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::mainPanel()
{
    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);

    ImGui::Begin("Configure Panel");
    if (ImGui::Button("Report"))
    {
        report();
    }
    ImGui::SeparatorText("Usage");
    ImGui::Text("1. WASDQE to move camara.\n2. Press ALT + WASD to rotate camara.\n 3. Choose a part to modify.\n 4. Press \"Report\" to output transformation info of each parts.");
    ImGui::SeparatorText("Parts");
    // Part names array
    const char* partNames[] = {
        "Head",
        "Upper Body",
        "Lower Body",
        "Right Upper Arm",
        "Right Lower Arm",
        "Right Hand",
        "Left Upper Arm",
        "Left Lower Arm",
        "Left Hand",
        "Right Thigh",
        "Right Calf",
        "Right Foot",
        "Left Thigh",
        "Left Calf",
        "Left Foot"
    };

    
    ImGui::PushItemWidth(-1);  // Make ListBox fill available width
    if (ImGui::ListBox("##PartsList", &partSelected, partNames, IM_ARRAYSIZE(partNames), IM_ARRAYSIZE(partNames)))
    {
        Robot* robot = &scene->getRobot();
        selectedNode = &robot->getNode(partSelected);
    }
    ImGui::PopItemWidth();
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_FirstUseEver);
    ImGui::Begin("Transformation of the Robot");
    transformPanel(selectedNode);
    ImGui::End();

}

void GUI::transformPanel(Node* node)
{    
    glm::vec3 trans = node->getTranslateOffset();
    glm::vec3 angle = node->getRotateAngle();

    ImGui::SeparatorText("Translation");
    if (ImGui::DragFloat("x (Translate)", &trans[0], 0.05f, -FLT_MAX, FLT_MAX, "%.3f"))
    {
        node->setTranslate(trans);
    }
    if (ImGui::DragFloat("y (Translate)", &trans[1], 0.05f, -FLT_MAX, FLT_MAX, "%.3f"))
    {
        node->setTranslate(trans);
    }
    if (ImGui::DragFloat("z (Translate)", &trans[2], 0.05f, -FLT_MAX, FLT_MAX, "%.3f"))
    {
        node->setTranslate(trans);
    }

    ImGui::SeparatorText("Rotation");
    if (ImGui::DragFloat("x (Rotate)", &angle[0], 0.05f, -360.0f, 360.0f, "%.3f"))
    {
        node->setRotate(angle);
    }
    if (ImGui::DragFloat("y (Rotate)", &angle[1], 0.05f, -360.0f, 360.0f, "%.3f"))
    {
        node->setRotate(angle);
    }
    if (ImGui::DragFloat("z (Rotate)", &angle[2], 0.05f, -360.0f, 360.0f, "%.3f"))
    {
        node->setRotate(angle);
    }
}

void GUI::_render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::report()
{
    for (int i = 0; i < 15; i++)
    {
        Node* node = &(robot->getNode(i));
        std::cout << "Node " << i << " have\nTranslation vector : " << glm::to_string(node->getTranslateOffset()) << std::endl <<
            "Rotation angle: " << glm::to_string(node->getRotateAngle()) << std::endl << std::endl;
    }
}
