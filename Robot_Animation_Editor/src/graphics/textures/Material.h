#pragma once
#include <vector>
#include <string>

#include "TextureCache.h"

#include "glm/glm.hpp"

#define MAP_KD 0	// Base color texture file. During rendering, the map_Kd value is multiplied by the Kd value.
#define MAP_NS 1	// Scalar texture file. During rendering, the map_Ns value is multiplied by the Ns value.
#define MAP_REFL 2	// Metallic maps
#define MAP_KE 3	// Emissive texture.
#define MAP_D 4		// Scalar texture file. During rendering, the map_d value is multiplied by the d value.
#define MAP_BUMP 5	// Normal in our robot case

struct MaterialKey // map file nnames as a key
{
	std::string prefix;
	std::string mapKdPath;
	std::string mapNsPath;
	std::string mapReflPath;
	std::string mapKePath;
	std::string mapDPath;
	std::string mapBumpPath;
};

std::string concatMatKey(const MaterialKey& key);

class Material
{
private:
	std::string matFileName[6];

	MaterialKey key; // store mapping file path
	std::string strKey; // key to access MaterialManager 

public :
	Material();
	Material(const MaterialKey& _key);
	~Material() {}

	void LoadMTL();
	void loadTextures();

	void initialize(const MaterialKey& _key);
	void use(std::vector<int> units);
};
