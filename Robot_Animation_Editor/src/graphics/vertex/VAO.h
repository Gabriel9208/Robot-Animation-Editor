#pragma once

class VAO
{
private:
	unsigned int id;

public:
	VAO();
	VAO(VAO&& other) noexcept;
	VAO(const VAO& other) = delete; 

	~VAO();

	VAO& operator=(const VAO& other) = delete;
	VAO& operator=(VAO&& other) noexcept;


	void bind() const;
	void unbind() const;
};