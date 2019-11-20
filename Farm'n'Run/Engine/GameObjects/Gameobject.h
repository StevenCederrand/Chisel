#ifndef _GAMEOBJECT_h
#define _GAMEOBJECT_h
#include <PCH/pch.h>
#include <Engine/Gameobjects/Mesh.h>
#include <Engine/Utility/Loader/MeshLoader.h>


enum ObjectType {
	STATIC_OBJECT,
};

struct Transform {
	glm::vec3 scale;
	glm::vec3 position;
	glm::quat rotation;
	glm::mat4 matrix;
};

class GameObject {
public:
	GameObject();
	GameObject(std::string name);//Still creating an empty
	GameObject(const std::string& name, const std::string& filePath, const ObjectType& objType); //Load a mesh

	~GameObject();

	
	void loadMesh(std::string filePath);

	void setMesh(Mesh* mesh);
	void setMesh(std::vector<Mesh*> mesh);
	std::vector<Mesh*> getMesh() const;

	const Transform& getTransform() const;
	void setWorldPosition(const glm::vec3& position);
	void setRotation(const glm::quat& rotation);
	void setScale(const glm::vec3& scale);

	void translate(const glm::vec3& position);

private:
	void updateMatrix(); 

	Transform m_transform;
	
	std::vector<Mesh*> m_meshes;
	ObjectType m_type;
	std::string m_name;

};

#endif