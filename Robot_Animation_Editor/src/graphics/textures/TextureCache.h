#pragma once

#include <unordered_map>
#include <string>

#include "Texture.h"

class TextureCache
{
private:
	TextureCache() {}
	~TextureCache() {}

	static TextureCache instance;
	std::unordered_map<std::string, Texture> fileTexMap;

	std::unordered_map<std::string, unsigned int> activeTextures;
	std::unordered_map<unsigned int, std::string> usedUnits;

public:
	static TextureCache& getInstance();

	void loadTexture(const std::string& path, int type);
	bool find(const std::string& path) const;
	void bind(const std::string& path, const int& textureUnit = 0);
	void clearBindings();
	bool unitUsed(unsigned int unit);
	bool textureBined(const std::string& key);
};

