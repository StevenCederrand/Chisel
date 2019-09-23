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

void MaterialMap::insertMat(const std::string& name, Material mat)
{
	//If the material exists
	if (existsWithName(name)) {
		return;
	}

	//If we have enough information to bind textures	
	m_materials[name] = mat;
	m_materials[name].hasBoundTextures = true; //we state that the texture that we have in memory are bound
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

	if (it->second.hasBoundTextures) {
		for (int i = 0; i < it->second.textures.size(); i++) {
			m_textureMap.removeTexture(it->second.textures.at(i).first);
		}
	}
}