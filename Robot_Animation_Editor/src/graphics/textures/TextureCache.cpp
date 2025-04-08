#include "TextureCache.h"
#include <iostream>

TextureCache TextureCache::instance;

TextureCache& TextureCache::getInstance()
{
	return instance;
}

void TextureCache::loadTexture(const std::string& path, int type)
{
	if(find(path))
	{
		return;
	}

	fileTexMap[path] = std::move(Texture(path.c_str(), type));
}

bool TextureCache::find(const std::string& path) const
{
	if (fileTexMap.find(path) != fileTexMap.end())
	{
		return true;
	}
	return false;
}

void TextureCache::bind(const std::string& path, const int& textureUnit /* = 0 */)
{
	if (!find(path)) 
	{
		return;
	}

	if (!textureBined(path))
	{
		if (unitUsed(textureUnit) && usedUnits[textureUnit] != path)
		{
			for (int unit = 0; unit < 32; unit++)
			{
				if (unit == textureUnit)
				{
					continue;
				}
				if (!unitUsed(unit))
				{
					usedUnits[unit] = path;
					activeTextures[path] = unit;
					fileTexMap[path].bind(unit);
					return;
				}
			}
			std::cout << "Texture unit is full and the texture located at unit " << textureUnit << " will be replaced." << std::endl;

		}

		usedUnits[textureUnit] = path;
		activeTextures[path] = textureUnit;
		fileTexMap[path].bind(textureUnit);
	}
}

void TextureCache::clearBindings()
{
	activeTextures.clear();
	usedUnits.clear();
}

bool TextureCache::unitUsed(unsigned int unit)
{
	if (usedUnits.find(unit) != usedUnits.end())
	{
		return true;
	}
	return false;
}

bool TextureCache::textureBined(const std::string& key)
{
	if (activeTextures.find(key) != activeTextures.end())
	{
		return true;
	}
	return false;
}
