#include "PCH/pch.h"
#include "MaterialMap.h"

MaterialMap* MaterialMap::m_materialMap;

MaterialMap::MaterialMap() {
}

MaterialMap::~MaterialMap() {

}

MaterialMap* MaterialMap::getInstance()
{
	if (m_materialMap == nullptr) {
		m_materialMap = new MaterialMap();
	}
	return m_materialMap;
}

void MaterialMap::destroy()
{
	cleanUp();
	delete m_materialMap;
}

void MaterialMap::cleanUp()
{
	std::map<std::string, Material*>::iterator it;
	for (it = m_materials.begin(); it != m_materials.end(); it++) {
		delete it->second;
	}
	m_materials.clear();
}

bool MaterialMap::existsWithName(const std::string& name) {

	if (m_materials.find(name) != m_materials.end()) {
		return true;
	}

	return false;
}

Material* MaterialMap::insertMat(const std::string& name, Material* mat)
{
	//If the material exists
	if (existsWithName(name)) {
		return m_materials[name];
	}

	//If we have enough information to bind textures	
	m_materials[name] = mat;
	return mat;
}

Material* MaterialMap::getMaterial(const std::string& name)
{
	if (existsWithName(name)) {
		return m_materials[name];
	}
	return nullptr;
}

void MaterialMap::remove(const std::string& name)
{
	if (!existsWithName(name)) {
		return;
	}
	
	if (m_materials.find(name) != m_materials.end()) {
		delete m_materials[name];
		m_materials.erase(name);
	}
}