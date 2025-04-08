#include "EBO.h"
#include "../../utils/Error.h"

#include <GL/glew.h>


EBO::EBO(): count(0)
{
	GLCall(glCreateBuffers(1, &id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

EBO::EBO(const std::vector<unsigned int>& v)
{
	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.size() * sizeof(unsigned int), &v[0], GL_STATIC_DRAW));
	count = v.size();
}

EBO::EBO(EBO&& other) noexcept : id(other.id), count(other.count)
{
	other.id = 0;
}

EBO::~EBO()
{
	if (id != 0) {
		GLCall(glDeleteBuffers(1, &id));
	}
}

EBO& EBO::operator=(EBO&& other) noexcept
{
	if (this != &other) 
	{
		if (id != 0)
		{
			glDeleteBuffers(1, &id);
		}

		count = other.count;

		id = other.id;
		other.id = 0;
	}

	return *this;
}


void EBO::initialize(const std::vector<unsigned int>& v)
{
	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.size() * sizeof(unsigned int), &v[0], GL_STATIC_DRAW));
	count = v.size();
}

void EBO::bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
}

void EBO::unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
