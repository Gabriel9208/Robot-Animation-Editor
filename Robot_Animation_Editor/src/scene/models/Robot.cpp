#include "Robot.h"

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

Robot::Robot()
{
	parts.emplace_back(Node("head.obj", "head.mtl", "res/robot/"));
	parts.emplace_back(Node("top_body.obj", "top_body.mtl", "res/robot/"));
	parts.emplace_back(Node("bottom_body.obj", "bottom_body.mtl", "res/robot/"));
	parts.emplace_back(Node("right_upper_arm.obj", "right_upper_arm.mtl", "res/robot/"));
	parts.emplace_back(Node("right_lower_arm.obj", "right_lower_arm.mtl", "res/robot/"));
	parts.emplace_back(Node("right_hand.obj", "right_hand.mtl", "res/robot/"));
	parts.emplace_back(Node("left_upper_arm.obj", "left_upper_arm.mtl", "res/robot/"));
	parts.emplace_back(Node("left_lower_arm.obj", "left_lower_arm.mtl", "res/robot/"));
	parts.emplace_back(Node("left_hand.obj", "left_hand.mtl", "res/robot/"));
	parts.emplace_back(Node("right_thigh.obj", "right_thigh.mtl", "res/robot/"));
	parts.emplace_back(Node("right_calf.obj", "right_calf.mtl", "res/robot/"));
	parts.emplace_back(Node("right_foot.obj", "right_foot.mtl", "res/robot/"));
	parts.emplace_back(Node("left_thigh.obj", "left_thigh.mtl", "res/robot/"));
	parts.emplace_back(Node("left_calf.obj", "left_calf.mtl", "res/robot/"));
	parts.emplace_back(Node("left_foot.obj", "left_foot.mtl", "res/robot/"));

	parts[TOP_BODY].addChildren(std::vector<Node*>({ &parts[HEAD], &parts[BOTTOM_BODY], &parts[RIGHT_UPPER_ARM], &parts[LEFT_UPPER_ARM] }));
	parts[BOTTOM_BODY].addChildren(std::vector<Node*>({ &parts[RIGHT_THIGH], &parts[LEFT_THIGH] }));

	parts[RIGHT_UPPER_ARM].addChildren(std::vector<Node*>({ &parts[RIGHT_LOWER_ARM] }));
	parts[RIGHT_LOWER_ARM].addChildren(std::vector<Node*>({ &parts[RIGHT_HAND] }));
	parts[LEFT_UPPER_ARM].addChildren(std::vector<Node*>({ &parts[LEFT_LOWER_ARM] }));
	parts[LEFT_LOWER_ARM].addChildren(std::vector<Node*>({ &parts[LEFT_HAND] }));

	parts[RIGHT_THIGH].addChildren(std::vector<Node*>({ &parts[RIGHT_CALF] }));
	parts[RIGHT_CALF].addChildren(std::vector<Node*>({ &parts[RIGHT_FOOT] }));
	parts[LEFT_THIGH].addChildren(std::vector<Node*>({ &parts[LEFT_CALF] }));
	parts[LEFT_CALF].addChildren(std::vector<Node*>({ &parts[LEFT_FOOT] }));

	standMotion();
}

void Robot::render(Renderer& renderer, const Camara& camara, const ShaderProgram& program)
{
	renderer.clear();
	for (int i = 0; i < parts.size(); i++)
	{
		renderer.drawElement(program, parts[i], camara);
	}
}

void Robot::standMotion()
{
	parts[0].setTranslate(glm::vec3(0.000000, 3.100000, 0.000000));
	parts[1].setTranslate(glm::vec3(0.000000, 0.000000, 0.000000));
	parts[2].setTranslate(glm::vec3(0.000000, -3.550000, 0.000000));
	parts[3].setTranslate(glm::vec3(-7.650000, 0.050000, 0.000000));
	parts[4].setTranslate(glm::vec3(-2.950000, -6.400000, 0.000000));
	parts[5].setTranslate(glm::vec3(-11.250000, -8.500000, 3.900000));
	parts[6].setTranslate(glm::vec3(7.650000, 0.000000, 0.000000));
	parts[7].setTranslate(glm::vec3(2.900000, -6.400000, 0.000000));
	parts[8].setTranslate(glm::vec3(11.200000, -8.500000, 3.900000));
	parts[9].setTranslate(glm::vec3(-3.250000, -6.650000, 2.200000));
	parts[10].setTranslate(glm::vec3(-3.350000, -13.100000, 1.150000));
	parts[11].setTranslate(glm::vec3(-4.700000, -23.150000, 1.100000));
	parts[12].setTranslate(glm::vec3(3.250000, -6.650000, 2.200000));
	parts[13].setTranslate(glm::vec3(3.200000, -13.100000, 1.150000));
	parts[14].setTranslate(glm::vec3(4.550000, -23.150000, 1.100000));
}
