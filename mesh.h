#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec3 color;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices);
	~Mesh();

	void render();
private:
	unsigned int vaoId, vboId;

	std::vector<Vertex> vertices;
};

