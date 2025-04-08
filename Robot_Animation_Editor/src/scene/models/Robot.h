#pragma once

#include <vector>

#include "Object.h"
#include "../graphics/Renderer.h"
#include "../camara/Camara.h"
#include "../graphics/shaders/ShaderProgram.h"

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


class Robot
{
private:
	std::vector<Object> parts;

public:
	Robot();
	~Robot() {}

	void render(Renderer& renderer, const Camara& camara, const ShaderProgram& program);
};

