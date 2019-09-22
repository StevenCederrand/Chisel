#include "PCH/pch.h"
#include "Gameobject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
	for (int i = 0; i < m_meshes.size(); i++) {
		delete m_meshes[i];
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
