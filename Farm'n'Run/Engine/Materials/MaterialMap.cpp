#include "PCH/pch.h"
#include "MaterialMap.h"

MaterialMap* MaterialMap::m_materialMap;


MaterialMap* MaterialMap::getInstance()
{
	if (m_materialMap == nullptr) {
		m_materialMap = new MaterialMap();
	}
	return m_materialMap;
}

void MaterialMap::destroy()
{
	delete m_materialMap;
}

void MaterialMap::cleanUp()
{
}

bool MaterialMap::existsWithName(const std::string& name) {

	if (m_materials.find(name) != m_materials.end()) {
		return true;
	}

	return false;
}

void MaterialMap::insertMat(const std::string& name, Material mat, std::vector<std::string> texturePaths)
{
	//If the material exists
	if (existsWithName(name)) {
		return;
	}
	
	
	if (mat.textures.size() != texturePaths.size()) {
		logError("Error creating material textures. Not enough paths input compared to names!");
		m_materials[name] = mat;
		return;
	}



	//If we have enough information to bind textures	
	m_materials[name] = mat;
	m_materials[name].hasBoundTextures = true; //we state that the texture that we have in memory are bound
	/*
	for (int i = 0; i < mat.textureNames.size(); i++) {
		m_textureMap.insert(mat.textureNames.at(i), texturePaths.at(i));
	}*/
}

const Material& MaterialMap::getMaterial(const std::string& name)
{
	if (existsWithName(name)) {
		return m_materials[name];
	}
	return Material();
}

void MaterialMap::remove(const std::string& name)
{
	if (!existsWithName(name)) {
		return;
	}

	std::map<std::string, Material>::iterator it;
	it = m_materials.find(name);
	m_materials.erase(it);

	//if (it->second.hasBoundTextures) {
	//	for (int i = 0; i < it->second.textureNames.size(); i++) {
	//		//m_textureMap.removeTexture(it->second.textureNames.at(i));
	//	}
	//}
}