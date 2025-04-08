#include "ShaderProgram.h"
#include "../../utils/Error.h"

#include <fstream>
#include <sstream>
#include <iostream>

ShaderProgram::ShaderProgram()
{
	GLCall(program = glCreateProgram());
}

ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteProgram(program));
}

std::string ShaderProgram::loadShader(const std::string& path) const
{
	std::ifstream shaderFile(path);
	std::stringstream shaderContent;
	std::string line;

	while(std::getline(shaderFile, line))
	{
		shaderContent << line << std::endl;
	}

	return shaderContent.str();
}

void ShaderProgram::createShader(GLenum type, const std::string& path)
{
	GLCall(GLuint shader = glCreateShader(type));
	compileShader(shader, path);

	GLCall(glAttachShader(program, shader));
	GLCall(glLinkProgram(program));

	GLCall(glDeleteShader(shader));
}

void ShaderProgram::use() const
{
	GLCall(glUseProgram(program));
}

void ShaderProgram::unUse() const
{
	GLCall(glUseProgram(0));

}

void ShaderProgram::compileShader(unsigned int shader, const std::string& path)
{
	std::string shaderContent = loadShader(path);
	const char* shaderContentPtr = shaderContent.c_str();
	GLCall(glShaderSource(shader, 1, &shaderContentPtr, nullptr));
	GLCall(glCompileShader(shader));

	int compileResult;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult));
	if (compileResult == GL_FALSE)
	{
		std::cout << "Shader: \"" << path << "\" compile failed." << std::endl;
	}
}
