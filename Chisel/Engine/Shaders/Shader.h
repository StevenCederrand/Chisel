#ifndef SHADER_h
#define SHADER_h
#include <PCH/pch.h>
#include <Engine/Materials/MaterialMap.h>

class Shader
{
public:
	Shader();
	Shader(std::string vertex, std::string fragment);
	Shader(std::string vertex, std::string geometry, std::string fragment);
	~Shader();

	void use();
	void unuse();

	void setMat3(std::string name, glm::mat3 mat);
	void setMat4(std::string name, glm::mat4 mat);
	void setVec3(std::string name, glm::vec3 vec);
	void setVec4(std::string name, glm::vec4 vec);
	void setFloat(std::string name, float num);
	void setInt(std::string name, int num);
	void setName(std::string name);
	void setMaterial(const Material& mat);
	void setMaterial(Material* mat);
	
	//Directional Light handles
	void direcionalLightData(const DirectionalLight& directionalLight);
	void bindDirectionalLight();

	bool getValid() const;
	int getShaderID() const;
	std::string getName() const;
	std::vector<std::string> getShaderNames() const;

	Shader& operator=(const Shader& other);
	
private:
	void shaderSetup(std::string shaderName, unsigned int& shader);
	bool m_valid;
	std::string m_name;
	int m_shaderProg;
	std::vector<std::string> m_shaderNames; //We need to save the name of the shaders. 
	DirectionalLight m_directionalLight;
};

#endif