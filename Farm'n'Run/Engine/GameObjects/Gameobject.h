#ifndef _GAMEOBJECT_h
#define _GAMEOBJECT_h
#include <PCH/pch.h>
#include <Engine/Gameobjects/Mesh.h>
#include <Engine/Utility/Loader/MeshLoader.h>


class GameObject {
public:
	GameObject();
	GameObject(std::string name);//Still creating an empty
	GameObject(const std::string& name, const std::string& filePath, int objType); //Load a mesh

	~GameObject();

	
	void loadMesh(std::string filePath);

	void setMesh(Mesh* mesh);
	void setMesh(std::vector<Mesh*> mesh);
	std::vector<Mesh*> getMesh() const;

	const glm::vec3& getWorldPostition() const;
	const glm::mat4& getModelMatrix() const;
	void setWorldPosition(const glm::vec3 position);
	void translate(const glm::vec3& position);

private:
	glm::mat4 m_modelMatrix;
	glm::vec3 m_worldPosition;
	std::vector<Mesh*> m_meshes;

	std::string m_name;

};

#endif