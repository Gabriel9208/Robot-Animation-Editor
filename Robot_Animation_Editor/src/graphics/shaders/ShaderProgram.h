#pragma once
#include <string>
#include <GL/glew.h>

class ShaderProgram
{
private:
	unsigned int program;

	void compileShader(unsigned int shader, const std::string& path);

public:
	ShaderProgram();
	~ShaderProgram();

	std::string loadShader(const std::string& path) const;
	void createShader(GLenum type, const std::string& path);

	void use() const;
	void unUse() const;

	inline unsigned int getId() const { return program; }
};