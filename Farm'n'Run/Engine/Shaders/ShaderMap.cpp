#include <PCH/pch.h>
#include "ShaderMap.h"


//std::map<std::string, Shader*> ShaderMap::m_shaderMap;
ShaderMap* ShaderMap::m_shaderMapInstance = 0;

ShaderMap::ShaderMap() {}


ShaderMap* ShaderMap::getInstance()
{
	if (m_shaderMapInstance == 0) {
		m_shaderMapInstance = new ShaderMap();
	}
	return m_shaderMapInstance;
}

Shader* ShaderMap::createShader(const SHADER_ID& shaderID, std::string vsName, std::string fsName)
{
	//If we have already reserved the name
	if (existsWithName(shaderID)) {
		return nullptr;
	}

	Shader* shader = new Shader(vsName, fsName);
	m_shaderMap[shaderID] = shader;
	return shader;
}

Shader* ShaderMap::getShader(const SHADER_ID& shaderID)
{
	if (existsWithName(shaderID))
	{
		return m_shaderMap[shaderID];
	}

	return nullptr;
}

void ShaderMap::cleanUp()
{
	std::map<SHADER_ID, Shader*>::iterator it;

	for (it = m_shaderMap.begin(); it != m_shaderMap.end(); it++) {
		delete it->second;
	}

	m_shaderMap.clear();
}

bool ShaderMap::existsWithName(const SHADER_ID& shaderID)
{
	if (m_shaderMap.find(shaderID) != m_shaderMap.end()) {
		return true;
	}
	return false;
}

void ShaderMap::reload() {
	std::map<SHADER_ID, Shader*>::iterator it;

	for (it = m_shaderMap.begin(); it != m_shaderMap.end(); it++) {
		Shader* tempShader = new Shader(it->second->getShaderNames()[0], it->second->getShaderNames()[1]);
		if (tempShader->getValid()) {
			delete it->second;
			it->second = tempShader;

			logInfo("Recompile Shader Completed");
		}
		else {
			delete tempShader;
		}
	}

	for (it = m_shaderMap.begin(); it != m_shaderMap.end(); it++) {
		logTrace("Shader ID: {0}", it->second->getShaderID());
	}
}

Shader* ShaderMap::useByName(const SHADER_ID& shaderID) {

	if (existsWithName(shaderID)) {
		m_shaderMap[shaderID]->use();
		return m_shaderMap[shaderID];
	}
	return nullptr;
}

void ShaderMap::destroy()
{
	cleanUp();
	delete m_shaderMapInstance;
}
