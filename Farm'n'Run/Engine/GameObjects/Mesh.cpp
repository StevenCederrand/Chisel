#include <PCH/pch.h>
#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::string materialName) {
	m_vertices = vertices;
	m_indices = indices;
	m_materialName = materialName;

	setupMesh();
}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_renderBuffers.m_VAO);
	glDeleteBuffers(1, &m_renderBuffers.m_IBO);
	glDeleteBuffers(1, &m_renderBuffers.m_VBO);
}


const RenderBuffers& Mesh::getBuffers() const
{
	return m_renderBuffers;
}

int Mesh::getNrOfIndices()
{
	return m_indices.size();
}

const std::string& Mesh::getMaterialName() const
{
	return m_materialName;
}

void Mesh::setupMesh() {

	//Bind the vertex array
	glGenVertexArrays(1, &m_renderBuffers.m_VAO);
	//Bind and generate buffers
	glGenBuffers(1, &m_renderBuffers.m_VBO);
	glGenBuffers(1, &m_renderBuffers.m_IBO);
	
	glBindVertexArray(m_renderBuffers.m_VAO);
	//Setup Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_renderBuffers.m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
	//bind index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderBuffers.m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	
	glBindVertexArray(0);
}
