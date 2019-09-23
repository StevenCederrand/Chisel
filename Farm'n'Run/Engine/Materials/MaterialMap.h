#ifndef _MATERIALMAP_h
#define _MATERIALMAP_h
#include <PCH/pch.h>
#include <Engine/Textures/TextureMap.h>

struct Material {
	glm::vec3 ambientCol;
	glm::vec3 diffuseCol;
	glm::vec3 specCol;

	std::vector<std::pair<std::string, std::string>> textures; //Name --- type
	bool hasBoundTextures = false; //Set this only to true in the materialmap
};


class MaterialMap {
public:
	static MaterialMap* getInstance();
	//Invoke only when you clearly want to destroy the singleton
	void destroy();
	void cleanUp();

	//Assign a name to the material 
	void insertMat(const std::string& name, Material mat);
	const Material& getMaterial(const std::string& name);
	void remove(const std::string& name);

private:
	bool existsWithName(const std::string& name);
	static MaterialMap* m_materialMap;
	std::map<std::string, Material> m_materials;
	TextureMap m_textureMap;
};



#endif