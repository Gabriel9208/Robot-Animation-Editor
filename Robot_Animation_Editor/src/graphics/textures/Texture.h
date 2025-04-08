#pragma once

class Texture
{
private:
	unsigned int id;

	int width;
	int height;
	int bytesPerPixel;

	void createTexture();

public:
	Texture(): id(0), width(0), height(0), bytesPerPixel(0) {}
	Texture(const char* path, int type);

	Texture(const Texture& other) = delete;
	Texture(Texture&& other) noexcept;

	~Texture();

	Texture& operator=(const Texture& other) = delete;
	Texture& operator=(Texture&& other) noexcept;

	void initialize(const char* path, int type);
	void bind(unsigned int textureUnit = 0) const;

};

