#pragma once
#include <vector>

class EBO
{
private:
	unsigned int id;
	unsigned count;

public:
	EBO();
	EBO(const std::vector<unsigned int>& v);

	EBO(EBO&& other) noexcept;
	EBO(const EBO& other) = delete;

	~EBO();
	
	EBO& operator=(const EBO& other) = delete;
	EBO& operator=(EBO&& other) noexcept;


	void initialize(const std::vector<unsigned int>& v);

	void bind() const;
	void unbind() const;

	inline int getCount() const { return count; }
};