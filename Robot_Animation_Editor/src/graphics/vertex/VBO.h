#pragma once
#include <vector>
#include <GL/glew.h>
#include <iostream>

#include "../../utils/Error.h"

template<class T>
class VBO 
{
private:
	unsigned int id;

public:
	VBO(): id(0) {}
	VBO(const std::vector<T>& v);

	VBO(VBO&& other) noexcept;
	VBO(const VBO& other) = delete;

	~VBO();

	VBO& operator=(const VBO& other) = delete;
	VBO& operator=(VBO&& other) noexcept;

	void initialize(const std::vector<T>& v);

	void bind() const;
	void unbind() const;
};

template<class T>
VBO<T>::VBO(const std::vector<T>& v)
{
	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(T), &v[0], GL_STATIC_DRAW));
}

template<class T>
VBO<T>::VBO(VBO<T>&& other) noexcept : id(other.id)
{
	other.id = 0;
}


template<class T>
VBO<T>::~VBO()
{
	if (id != 0) 
	{
		GLCall(glDeleteBuffers(1, &id));
	}
}

template<class T>
VBO<T>& VBO<T>::operator=(VBO<T>&& other) noexcept
{
	if (this != &other) 
	{
		if (id != 0)
		{
			GLCall(glDeleteBuffers(1, &id));
		}

		id = other.id;
		other.id = 0;
	}
	
	return *this;
}

template<class T>
void VBO<T>::initialize(const std::vector<T>& v)
{
	if(v.size() == 0)
	{
		std::cout << "VBO initialization fails: Empty vector." << std::endl;
		return;
	}

	GLCall(glGenBuffers(1, &id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(T), &v[0], GL_STATIC_DRAW));
}

template<class T>
void VBO<T>::bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, id));
}

template<class T> 
void VBO<T>::unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
