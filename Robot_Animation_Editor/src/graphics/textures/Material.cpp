#include "Material.h"

#include <fstream>
#include <iostream>
#include <unordered_map>


Material::Material()
{
	for (int i = 0; i < 6; i++)
	{
		matFileName[i] = "";
	}
}

Material::Material(const MaterialKey& _key)
{
	initialize(_key);
}

void Material::LoadMTL()
{
	matFileName[MAP_KD] = key.prefix + key.mapKdPath;
	matFileName[MAP_NS] = key.prefix + key.mapNsPath;
	matFileName[MAP_REFL] = key.prefix + key.mapReflPath;
	matFileName[MAP_KE] = key.prefix + key.mapKePath;
	matFileName[MAP_D] = key.prefix + key.mapDPath;
	matFileName[MAP_BUMP] = key.prefix + key.mapBumpPath;
}

void Material::loadTextures()
{
	TextureCache& textureCache = TextureCache::getInstance();

	for (int i = 0; i < 1 /*6*/; i++)
	{
		textureCache.loadTexture(matFileName[i], i);
	}
}

void Material::initialize(const MaterialKey& _key)
{
	key = _key;
	strKey = concatMatKey(_key);
	LoadMTL();
	loadTextures();
}

void Material::use(std::vector<int> units)
{
	TextureCache& textureCache = TextureCache::getInstance();

	for (int i = 0; i < 1 /* 6 */; i++)
	{
		int unit = i < units.size() ? units[i] : i;
		textureCache.bind(matFileName[i], unit);
	}
}

std::string concatMatKey(const MaterialKey& key)
{
	return key.prefix + "|" + key.mapKdPath + "|" + key.mapNsPath + "|" + key.mapReflPath + "|" + key.mapKePath + "|" + key.mapDPath + "|" + key.mapBumpPath;
}
