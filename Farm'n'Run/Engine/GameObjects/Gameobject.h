#ifndef _GAMEOBJECT_h
#define _GAMEOBJECT_h
#include <PCH/pch.h>
#include <Engine/Gameobjects/Mesh.h>

class GameObject {
public:
	GameObject();
	~GameObject();

	
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

};

#endif