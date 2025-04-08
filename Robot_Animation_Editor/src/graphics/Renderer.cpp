#include "Renderer.h"
#include "../utils/Error.h"
#include "textures/MaterialManager.h"
#include "textures/TextureCache.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <GL/glew.h>

#define VERTICES_PER_FACE 3

Renderer Renderer::instance;

Renderer& Renderer::getInstance()
{
	return instance;
}

void Renderer::drawElement(const ShaderProgram& program, const Object& obj, const Camara& camara) const
{
	program.use();
	obj.bind();

	/*
	X: from about -5.7 to 5.9
	Y: from about -6.1 to 2.9
	Z: from about -23.9 to -16.4
	*/

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camara.lookAt();
	glm::mat4 orth = glm::ortho(-7.0f, 7.0f, -20.0f, 10.0f, -30.0f, 10.0f);

	glm::mat4 MVP = orth * view * model;

	GLCall(unsigned int programId = glGetUniformLocation(program.getId(), "u_MVP"));
	GLCall(glUniformMatrix4fv(programId, 1, GL_FALSE, &MVP[0][0]));

	std::vector<unsigned int> objFaces = obj.getFaces();
	std::vector<std::string> objmtls =  obj.getMatUsed();

	MaterialManager& mm = MaterialManager::getInstance();
	unsigned int accumIndices = 0;
	for (int i = 1; i < objFaces.size(); i++)
	{
		mm.use(objmtls[i - 1]);
		glDrawElements(GL_TRIANGLES, objFaces[i] * VERTICES_PER_FACE, GL_UNSIGNED_INT, (void*)(accumIndices * sizeof(GLuint)));
		accumIndices += objFaces[i] * VERTICES_PER_FACE;
	}
}

void Renderer::clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	TextureCache& tc = TextureCache::getInstance();
	tc.clearBindings();
}
