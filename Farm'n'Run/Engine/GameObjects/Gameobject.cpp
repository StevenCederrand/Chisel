#include "PCH/pch.h"
#include "Gameobject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(std::string name)
{
	m_name = name;
}
//By inputing a mesh, we will automatically submit it to the renderer
GameObject::GameObject(const std::string& name, const std::string& filePath, int objectType)
{
	m_name = name;
	loadMesh(filePath);
	Chisel::GetChisel()->chiselSubmit(this, objectType);
}

GameObject::~GameObject()
{	
	for (int i = 0; i < m_meshes.size(); i++) {
		delete m_meshes.at(i);
	}

}
//Loading the mesh into the system will automatically submit it to the renderer.
void GameObject::loadMesh(std::string filePath)
{
	MeshLoader meshLoader;

	//Interpret the mesh locally. The game doesn't really need to manage such things
	m_meshes = meshLoader.interpretMesh(filePath);

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
