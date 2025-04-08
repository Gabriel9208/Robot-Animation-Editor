#include "MaterialManager.h"

#include <fstream>
#include <iostream>

MaterialManager MaterialManager::instance;

void MaterialManager::parseMTL(const std::string& path, const std::string& prefix)
{
	std::ifstream inFile((prefix + path).c_str());

	if (!inFile)
	{
		std::cout << "Error occured when loading mtl file: \"" << path << "\", the file path might be wrong." << std::endl;
	}

	std::unordered_map<std::string, int> mtlMap;
	mtlMap["map_Kd"] = MAP_KD;
	mtlMap["map_Ns"] = MAP_NS;
	mtlMap["map_refl"] = MAP_REFL;
	mtlMap["map_Ke"] = MAP_KE;
	mtlMap["map_d"] = MAP_D;
	mtlMap["map_Bump"] = MAP_BUMP;

	std::string lineHead;
	std::string mtlName;
	MaterialKey key;
	key.prefix = prefix;
	key.mapKdPath = "";
	while (inFile >> lineHead)
	{
		std::string fileName;
		if (lineHead == "newmtl")
		{
			if (key.mapKdPath != "")
			{
				nameMapKey[mtlName] = concatMatKey(key);
				if (matMap.find(concatMatKey(key)) == matMap.end())
				{
					loadMTL(key);
				}
			}
			inFile >> lineHead;
			mtlName = lineHead;
		}
		else if (lineHead == "map_Kd" ||
			lineHead == "map_Ns" ||
			lineHead == "map_refl" ||
			lineHead == "map_Ke" ||
			lineHead == "map_d" ||
			lineHead == "map_Bump")
		{
			if (lineHead == "map_Bump")
			{
				std::string garbage;
				inFile >> garbage >> garbage;
			}

			while (1)
			{
				std::string path;
				inFile >> path;
				fileName += path + " ";
				if (path.find("png") != std::string::npos)
				{
					fileName = fileName.substr(0, fileName.size() - 1);
					break;
				}
			}

			switch (mtlMap[lineHead])
			{
			case MAP_KD:
				key.mapKdPath = fileName;
				break;
			case MAP_NS:
				key.mapNsPath = fileName;
				break;
			case MAP_REFL:
				key.mapReflPath = fileName;
				break;
			case MAP_KE:
				key.mapKePath = fileName;
				break;
			case MAP_D:
				key.mapDPath = fileName;
				break;
			case MAP_BUMP:
				key.mapBumpPath = fileName;
				break;
			}
		}
		else
		{
			std::getline(inFile, lineHead);
		}
	}

	nameMapKey[mtlName] = concatMatKey(key);
	if (matMap.find(concatMatKey(key)) == matMap.end())
	{
		loadMTL(key);
	}
}

MaterialManager& MaterialManager::getInstance()
{
	return instance;
}

void MaterialManager::registerMtl(const std::string& mtlFileName, const std::string& prefix /* = "res/robot/" */)
{
	parseMTL(mtlFileName, prefix);
}

void MaterialManager::use(const std::string& name, const std::vector<int>& units /* = std::vector<int>(0) */)
{
	if (nameMapKey.find(name) == nameMapKey.end() || matMap.find(nameMapKey[name]) == matMap.end())
	{
		std::cout << "Material \"" << name << "\" is not loaded." << std::endl;
		return;
	}
	matMap[nameMapKey[name]].use(units);
}

void MaterialManager::loadMTL(const MaterialKey& key)
{
	matMap[concatMatKey(key)] = Material(key);
}

