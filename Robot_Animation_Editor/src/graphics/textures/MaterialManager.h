#pragma once

#include <unordered_map>
#include <string>

#include "Material.h"

class MaterialManager
{
private:
	static MaterialManager instance;
	std::unordered_map<std::string, std::string> nameMapKey;
	std::unordered_map<std::string, Material> matMap; // key is string concatinate of MaterialKey

	MaterialManager() {}
	~MaterialManager() {}

	void loadMTL(const MaterialKey& key);
	void parseMTL(const std::string& path, const std::string& prefix);

public:
	static MaterialManager& getInstance();

	void registerMtl(const std::string& mtlFileName, const std::string& prefix = "res/robot/");
	void use(const std::string& name, const std::vector<int>& units = std::vector<int>(0));

	inline Material& getMat(const std::string& key) { return matMap[key]; }
};

