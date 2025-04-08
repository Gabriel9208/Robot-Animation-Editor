#include "GUI.h"

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
    defineInterface();
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

void GUI::defineInterface()
{
    ImGui::Begin("Parts of the Robot");
    // Header section
    ImGui::SeparatorText("Usage");
    ImGui::Text("Choose a part to modify.");
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

    // Option 1: Using ListBox with full-width items (requires padding hack)
    ImGui::PushItemWidth(-1);  // Make ListBox fill available width
    if (ImGui::ListBox("##PartsList", &partSelected, partNames, IM_ARRAYSIZE(partNames), IM_ARRAYSIZE(partNames)))
    {
        switch (partSelected) {
        case HEAD:
        case TOP_BODY:
        case BOTTOM_BODY:
        case RIGHT_UPPER_ARM:
        case RIGHT_LOWER_ARM:
        case RIGHT_HAND:
        case LEFT_UPPER_ARM:
        case LEFT_LOWER_ARM:
        case LEFT_HAND:
        case RIGHT_THIGH:
        case RIGHT_CALF:
        case RIGHT_FOOT:
        case LEFT_THIGH:
        case LEFT_CALF:
        case LEFT_FOOT:
            break;
        }
    }
    ImGui::PopItemWidth();
    ImGui::End();
}

void GUI::_render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


