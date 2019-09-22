#ifndef _SHADERMAP_h
#define _SHADERMAP_h
#include <PCH/pch.h>
#include <Engine/Shaders/Shader.h>

class ShaderMap {
public:
	static ShaderMap* getInstance();
	//@ vsName & fsName enter just the name of the shader.
	Shader* createShader(std::string name, std::string vsName, std::string fsName);
	Shader* getShader(std::string name);
	void cleanUp();
	bool existsWithName(std::string name);
	void reload();
	void useByName(std::string name);

	void destroy();
private:
	ShaderMap();
	static ShaderMap* m_shaderMapInstance;
	std::map<std::string, Shader*> m_shaderMap;
};



#endif