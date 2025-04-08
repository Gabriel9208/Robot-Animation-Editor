#include <fstream>
#include <iostream>
#include <sstream>

#include "Object.h"
#include "../graphics/textures/MaterialManager.h"
#include "../utils/Error.h"

#include "glm/glm.hpp"


Object::Object(const std::string& modelPath,
				const std::string& mtlPath,
				const std::string& filePrefix /* = "res/robot/" */
)
{
	loadOBJ((filePrefix + modelPath).c_str());
	fillInBuffers();

	MaterialManager& mm = MaterialManager::getInstance();
	mm.registerMtl(mtlPath, filePrefix);
}

Object::Object(Object&& other) noexcept:
	vertices(std::move(other.vertices)),
	normals(std::move(other.normals)),
	textures(std::move(other.textures)),
	arrangedVertex(std::move(other.arrangedVertex)),
	vertexIndex(std::move(other.vertexIndex)),
	facesPerMaterial(std::move(other.facesPerMaterial)),
	mtlNames(std::move(other.mtlNames)),
	vertexArray(std::move(other.vertexArray)),
	vertexBuffer(std::move(other.vertexBuffer)),
	vertexIndexBuffer(std::move(other.vertexIndexBuffer))
{}

Object& Object::operator=(Object&& other) noexcept
{
	if (this != &other)
	{
		vertices			= std::move(other.vertices);
		normals				= std::move(other.normals);
		textures			= std::move(other.textures);
		arrangedVertex		= std::move(other.arrangedVertex);
		vertexIndex			= std::move(other.vertexIndex);
		facesPerMaterial	= std::move(other.facesPerMaterial);
		mtlNames			= std::move(other.mtlNames);
		vertexArray			= std::move(other.vertexArray);
		vertexBuffer		= std::move(other.vertexBuffer);
		vertexIndexBuffer	= std::move(other.vertexIndexBuffer);
	}

	return *this;
}

void Object::loadOBJ(const char* path)
{
	std::ifstream inFile(path);
	std::unordered_map<std::string, int> faceIndexMap; // map face(1/2/3) to index(2)
	unsigned int faceCount = 0;

	if (!inFile)
	{
		std::cout << "Error occured when loading obj file: \"" << path << "\", the file path might be wrong." << std::endl;
	}

	std::string lineHead;
	while (inFile >> lineHead)
	{
		if (lineHead == "v")
		{
			glm::vec3 tmpVertex;
			inFile >> tmpVertex.x >> tmpVertex.y >> tmpVertex.z;
			vertices.emplace_back(tmpVertex);
		}
		else if (lineHead == "vn")
		{
			glm::vec3 tmpNormal;
			inFile >> tmpNormal.x >> tmpNormal.y >> tmpNormal.z;
			normals.emplace_back(tmpNormal);
		}
		else if (lineHead == "vt")
		{
			glm::vec2 tmpTexture;
			inFile >> tmpTexture.x >> tmpTexture.y;
			textures.emplace_back(tmpTexture);
		}
		else if (lineHead == "f")
		{
			std::string faceInfo;
			for (int i = 0; i < 3; i++)
			{
				inFile >> faceInfo;

				std::istringstream issFaceInfo(faceInfo);
				std::string index;

				Vertex tmpVertex;
				for (int j = 0; j < 3; j++)
				{
					std::getline(issFaceInfo, index, '/');
					switch (j) {
					case 0:
						tmpVertex.v = vertices[std::stoul(index) - 1]; // Obj file index start from 1
						break;
					case 1:
						tmpVertex.t = textures[std::stoul(index) - 1];
						break;
					case 2:
						tmpVertex.n = normals[std::stoul(index) - 1];
						break;
					}
				}

				if (faceIndexMap.find(faceInfo) == faceIndexMap.end()) 
				{
					arrangedVertex.emplace_back(tmpVertex);
					faceIndexMap[faceInfo] = arrangedVertex.size() - 1;
				}
				
				vertexIndex.emplace_back(faceIndexMap[faceInfo]);
			}
			faceCount++;
			
		}
		else if (lineHead == "usemtl")
		{
			std::string mtlName;
			inFile >> mtlName;
			facesPerMaterial.emplace_back(faceCount);
			mtlNames.emplace_back(mtlName);
			faceCount = 0;
		}
		else
		{
			std::getline(inFile, lineHead);
		}
	}
	facesPerMaterial.emplace_back(faceCount);
}

void Object::fillInBuffers()
{
	vertexArray.bind();
	vertexBuffer.bind();
	vertexIndexBuffer.bind();

	vertexBuffer.initialize(arrangedVertex);
	vertexIndexBuffer.initialize(vertexIndex);
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0));
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float))));
	GLCall(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(5 * sizeof(float))));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
}

void Object::bind() const
{
	vertexArray.bind();
}

void Object::unbind() const
{
	vertexArray.unbind();
}
