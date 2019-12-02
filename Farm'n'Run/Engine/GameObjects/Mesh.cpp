#include <PCH/pch.h>
#include "Mesh.h"


Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	m_vertices = vertices;
	m_indices = indices;
	setupMesh();

}

Mesh::~Mesh() {
	glDeleteVertexArrays(1, &m_renderBuffers.m_VAO);
	glDeleteBuffers(1, &m_renderBuffers.m_IBO);
	glDeleteBuffers(1, &m_renderBuffers.m_VBO);
}

void Mesh::addMaterial(Material* mat)
{
	m_materials.push_back(mat);
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

Material* Mesh::getMaterialAt(const int& i)
{
	if (i > m_materials.size() || i < 0) {
		return nullptr;
	}
	else {
		return m_materials[i];
	}
}

const std::vector<Material*>& Mesh::getMaterials() const
{
	return m_materials;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	glBindVertexArray(0);
}
