#ifndef _SHADERMAP_h
#define _SHADERMAP_h
#include <PCH/pch.h>
#include <Engine/Shaders/Shader.h>


enum SHADER_ID {
	FORWARD,
	SKYBOX,
};


class ShaderMap {
public:
	static ShaderMap* getInstance();
	//@ vsName & fsName enter just the name of the shader.
	Shader* createShader(const SHADER_ID& shaderID, std::string vsName, std::string fsName);
	Shader* getShader(const SHADER_ID& shaderID);
	void cleanUp();
	bool existsWithName(const SHADER_ID& shaderID);
	void reload();
	Shader* useByName(const SHADER_ID& shaderID);

	void destroy();
private:
	ShaderMap();

	static ShaderMap* m_shaderMapInstance;
	std::map<SHADER_ID, Shader*> m_shaderMap;
};



#endif