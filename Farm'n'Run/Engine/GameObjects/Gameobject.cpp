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
GameObject::GameObject(const std::string& name, const std::string& filePath, const ObjectType& objectType)
{
	m_name = name;
	loadMesh(filePath);
	Renderer::getInstance()->submit(this, objectType);
	m_type = objectType;
	//Initialize the transform
	setPosition(glm::vec3(0.0f));
	setScale(glm::vec3(1.0f));
	setRotation(glm::quat(glm::vec3(0, 0, 0)));

}

GameObject::~GameObject()
{	
	for (Mesh* mesh : m_meshes) {
		delete mesh;
	}

}
//Loading the mesh into the system will automatically submit it to the renderer.
void GameObject::loadMesh(std::string filePath)
{
	MeshLoader meshLoader;

	//Interpret the mesh locally. The game doesn't really need to manage such things
	m_meshes = meshLoader.interpretMesh(filePath);

	//TextureMap::getInstance()->dump();

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

const Transform& GameObject::getTransform() const {
	return m_transform;
}

void GameObject::setPosition(const glm::vec3& position)
{
	m_transform.position = position;
	updateMatrix();
}

void GameObject::setRotation(const glm::quat& rotation)
{
	m_transform.rotation = rotation;
	updateMatrix();
}

void GameObject::setScale(const glm::vec3& scale)
{
	m_transform.scale = scale;
	updateMatrix();
}

void GameObject::translate(const glm::vec3& position)
{
	m_transform.position += position;
	updateMatrix();
}

void GameObject::updateMatrix()
{
	m_transform.matrix = glm::mat4(1.0f);
	m_transform.matrix = glm::translate(m_transform.matrix, m_transform.position);
	m_transform.matrix *= glm::mat4_cast(m_transform.rotation);
	m_transform.matrix = glm::scale(m_transform.matrix, m_transform.scale);

}
