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



private:
	std::vector<Mesh*> m_meshes;



};

#endif