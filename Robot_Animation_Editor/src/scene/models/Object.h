#pragma once
#include <vector>
#include <string>
#include <unordered_map>

#include "../graphics/textures/Material.h"
#include "../graphics/vertex/VAO.h"
#include "../graphics/vertex/VBO.h"
#include "../graphics/vertex/EBO.h"

#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 v;
	glm::vec2 t;
	glm::vec3 n;
};

class Object 
{
private:
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> textures;

	std::vector<Vertex> arrangedVertex; // unique v/t/n pairs
	std::vector<unsigned int> vertexIndex; // index of v/t/n pairs

	std::vector<unsigned int> facesPerMaterial;
	std::vector<std::string> mtlNames; // key to access MaterialManager

	VAO vertexArray;
	VBO<Vertex> vertexBuffer;
	EBO vertexIndexBuffer;

public:
	Object(const std::string& modelPath, const std::string& mtlPath, const std::string& filePrefix = "res/robot/");
	Object(Object&& other) noexcept;
	~Object() {}

	Object& operator=(Object&& other) noexcept;

	void loadOBJ(const char* path);

	void fillInBuffers();

	void bind() const;
	void unbind() const;

	inline int getIndexCount() const { return vertexIndexBuffer.getCount(); }
	inline std::vector<unsigned int> getFaces() const { return facesPerMaterial; }
	inline std::vector<std::string> getMatUsed() const { return mtlNames; }
	
};