#include "Robot.h"

Robot::Robot()
{
	parts.emplace_back(Object("head.obj", "head.mtl", "res/robot/"));
	parts.emplace_back(Object("top_body.obj", "top_body.mtl", "res/robot/"));
	parts.emplace_back(Object("bottom_body.obj", "bottom_body.mtl", "res/robot/"));
	parts.emplace_back(Object("right_upper_arm.obj", "right_upper_arm.mtl", "res/robot/"));
	parts.emplace_back(Object("right_lower_arm.obj", "right_lower_arm.mtl", "res/robot/"));
	parts.emplace_back(Object("right_hand.obj", "right_hand.mtl", "res/robot/"));
	parts.emplace_back(Object("left_upper_arm.obj", "left_upper_arm.mtl", "res/robot/"));
	parts.emplace_back(Object("left_lower_arm.obj", "left_lower_arm.mtl", "res/robot/"));
	parts.emplace_back(Object("left_hand.obj", "left_hand.mtl", "res/robot/"));
	parts.emplace_back(Object("right_thigh.obj", "right_thigh.mtl", "res/robot/"));
	parts.emplace_back(Object("right_calf.obj", "right_calf.mtl", "res/robot/"));
	parts.emplace_back(Object("right_foot.obj", "right_foot.mtl", "res/robot/"));
	parts.emplace_back(Object("left_thigh.obj", "left_thigh.mtl", "res/robot/"));
	parts.emplace_back(Object("left_calf.obj", "left_calf.mtl", "res/robot/"));
	parts.emplace_back(Object("left_foot.obj", "left_foot.mtl", "res/robot/"));

}

void Robot::render(Renderer& renderer, const Camara& camara, const ShaderProgram& program)
{
	renderer.clear();
	for (int i = 0; i < parts.size(); i++)
	{
		renderer.drawElement(program, parts[i], camara);
	}
}
