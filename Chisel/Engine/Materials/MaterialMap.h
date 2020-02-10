#ifndef _MATERIALMAP_h
#define _MATERIALMAP_h
#include <PCH/pch.h>
#include <Engine/Textures/TextureMap.h>

struct Material {
	std::string name;
	glm::vec3 ambientCol;
	glm::vec3 diffuseCol;
	glm::vec3 specCol;

	std::vector<GLuint> textures; //Just check to see if this size > 0, if it is then we have bound textures
	
};


class MaterialMap {
public:
	static MaterialMap* getInstance();
	//Invoke only when you clearly want to destroy the singleton
	void destroy();
	void cleanUp();

	//Assign a name to the material 
	Material* insertMat(const std::string& name, Material* mat);
	Material* getMaterial(const std::string& name);
	void remove(const std::string& name);
	bool existsWithName(const std::string& name);
	

private:
	MaterialMap();
	~MaterialMap();
	static MaterialMap* m_materialMap;
	std::map<std::string, Material*> m_materials;
};



#endif