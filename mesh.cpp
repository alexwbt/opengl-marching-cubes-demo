#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(std::vector<Vertex> vertices)
{
	this->vertices = vertices;

	glGenVertexArrays(1, &vaoId);
	glGenBuffers(1, &vboId);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(vaoId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
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