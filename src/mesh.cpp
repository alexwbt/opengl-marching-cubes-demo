#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(std::vector<Vertex> vertices)
{
	this->vertices = vertices;

	unsigned long long vertexSize = sizeof(Vertex);
	unsigned long long vec3Size = sizeof(glm::vec3);

	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindVertexArray(vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * vertexSize, vertices.data(), GL_STATIC_DRAW);

	for (int i = 0; i < 3; i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(i * vec3Size));
	}
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vaoId);
	glDeleteBuffers(1, &vboId);
}

void Mesh::render()
{
	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, GLsizei(vertices.size()));
}