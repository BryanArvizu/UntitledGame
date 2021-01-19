#include "Mesh.h"
#include <glad/glad.h>

ret::Mesh::Mesh(const std::vector<ret::Vertex>& vertices, 
                const std::vector<unsigned int>& indices, 
                Material* mat)
{
	vertices_ = vertices;
	indices_ = indices;
	material = mat;

	SetupMesh();
}

ret::Mesh::~Mesh()
{
}

void ret::Mesh::SetupMesh()
{
	// Generate Buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(ret::Vertex), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int),
		&indices_[0], GL_STATIC_DRAW);

	// ATTRIBUTES
	glEnableVertexAttribArray(0);	// Vertex Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ret::Vertex), (void*)0);

	glEnableVertexAttribArray(1);	// Vertex Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ret::Vertex), (void*)offsetof(ret::Vertex, normal));

	glEnableVertexAttribArray(2);	// Vertex Texture UV
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ret::Vertex), (void*)offsetof(ret::Vertex, uv));

	glBindVertexArray(0);
}