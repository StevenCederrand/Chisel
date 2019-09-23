#include "PCH/pch.h"
#include "Gameobject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{	
	for (int i = 0; i < m_meshes.size(); i++) {
		delete m_meshes.at(i);
	}

}

void GameObject::setMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
}

void GameObject::setMesh(std::vector<Mesh*> mesh)
{
	m_meshes = mesh;
}

std::vector<Mesh*> GameObject::getMesh() const
{
	return m_meshes;
}

const glm::vec3& GameObject::getWorldPostition() const
{
	return m_worldPosition;
}

const glm::mat4& GameObject::getModelMatrix() const
{
	return m_modelMatrix;
}

void GameObject::setWorldPosition(const glm::vec3 position)
{
	m_worldPosition = position;
	m_modelMatrix = glm::translate(m_modelMatrix, m_worldPosition);
}

void GameObject::translate(const glm::vec3& position)
{
	m_worldPosition += position;
	m_modelMatrix = glm::translate(m_modelMatrix, m_worldPosition);
}
