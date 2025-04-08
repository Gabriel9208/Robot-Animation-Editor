#include "Texture.h"
#include "../../utils/Error.h"

#include "stb_image/stb_image.h"

#include <GL/glew.h>

#define MAP_KD 0
#define MAP_NS 1
#define MAP_REFL 2
#define MAP_KE 3
#define MAP_D 4
#define MAP_BUMP 5

void Texture::createTexture()
{
	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &id));
}

Texture::Texture(const char* path, int type)
{
	initialize(path, type);
}

Texture::Texture(Texture&& other) noexcept:
	id(other.id),
	width(other.width),
	height(other.height),
	bytesPerPixel(other.bytesPerPixel)
{
	other.id = 0;
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &id));
}

Texture& Texture::operator=(Texture&& other) noexcept
{
	id = other.id;
	other.id = 0;

	width = other.width;
	height = other.height;
	bytesPerPixel = other.bytesPerPixel;

	return *this;
}

void Texture::initialize(const char* path, int type)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* textureImage = stbi_load(path, &width, &height, &bytesPerPixel, 4);
	if (!textureImage) {
		std::cerr << "Failed to load texture: " << path << std::endl;
		return; // Exit early to avoid using invalid texture data
	}

	createTexture();
	GLCall(glBindTexture(GL_TEXTURE_2D, id));

	switch (type) {
		// base, emmisive, normal
	case MAP_KD:
	case MAP_KE:
	case MAP_BUMP:
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage));
		break;

		// grayscale(one channel): roughness, metallic, opacity
	case MAP_NS:
	case MAP_REFL:
	case MAP_D:
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, textureImage));
		break;
	}

	stbi_image_free(textureImage);
}

void Texture::bind(unsigned int textureUnit /* = 0 */) const
{
	if (textureUnit >= 32)
	{
		return;
	}

	GLCall(glActiveTexture(GL_TEXTURE0 + textureUnit));
	GLCall(glBindTexture(GL_TEXTURE_2D, id));
}