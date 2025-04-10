# Robot Animation Editor

A 3D robot model editor and animation tool built with OpenGL, allowing users to manipulate different robot parts and create various poses and animations.

## Features

- Interactive 3D robot model with 15 editable body parts
- Camera controls for rotating, panning, and zooming around the robot
- Real-time transformation controls for each body part:
  - Translation in X, Y, Z axes
  - Rotation in X, Y, Z axes
- Ability to report and export robot poses

## Controls

### Camera Navigation
- **W/S/A/D** - Move camera forward/backward/left/right
- **Q/E** - Move camera up/down
- **ALT + W/S/A/D** - Rotate camera
- **Middle Mouse Button** - Rotate camera (drag)
- **Right Mouse Button** - Pan camera (drag)

### Robot Editing
1. Select a robot body part from the list in the Configure Panel
2. Use the transformation controls to adjust its position and rotation
3. Click "Report" to output transformation information for all parts to console

## Available Body Parts

- Head
- Upper Body
- Lower Body
- Right Upper Arm
- Right Lower Arm
- Right Hand
- Left Upper Arm
- Left Lower Arm
- Left Hand
- Right Thigh
- Right Calf
- Right Foot
- Left Thigh
- Left Calf
- Left Foot

## Technical Information

Built using:
- C++ with OpenGL
- GLFW for window management
- GLEW for OpenGL extension loading
- ImGui for the user interface
- GLM for mathematics

## Building the Project

This project is set up as a Visual Studio solution. Open `Robot_Animation_Editor.vcxproj` in Visual Studio and build the solution.

## Project Structure

- `src/` - Source code
  - `App.cpp/h` - Main application entry point
  - `graphics/` - Rendering components
  - `scene/` - Scene management
    - `GUI/` - User interface components
    - `models/` - 3D models including the Robot
    - `camara/` - Camera implementation
    - `scene graph/` - Scene graph components for model manipulation
- `res/` - Resources
  - `robot/` - Robot model assets
  - `shaders/` - GLSL shader programs 