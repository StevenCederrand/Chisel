#include <Pch/Pch.h>
#include "Shader.h"

Shader::Shader() {

}

Shader::Shader(std::string vertex, std::string fragment)
{

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	GLint compileResult;
	char buffer[1024];
	shaderSetup(vertex, vertexShader);
	shaderSetup(fragment, fragmentShader);

	m_shaderProg = glCreateProgram();
	glAttachShader(m_shaderProg, vertexShader);
	glAttachShader(m_shaderProg, fragmentShader);
	glLinkProgram(m_shaderProg);

	glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		memset(buffer, 0, 1024);
		glGetProgramInfoLog(m_shaderProg, 1024, nullptr, buffer);
		logError("Error compiling shaders (vertexShader) {0} and (fragmentShader) {1} ", vertex, fragment);
		logInfo(buffer);
		m_valid = false;
	}

	glDetachShader(m_shaderProg, vertexShader);
	glDetachShader(m_shaderProg, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_valid = true;

}

Shader::Shader(std::string vertex, std::string geometry, std::string fragment)
{

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint compileResult;
	char buffer[1024];
	//m_shaderSetUp does Vertex, geometry and fragment shader setup
	shaderSetup(vertex, vertexShader);
	shaderSetup(geometry, geometryShader);
	shaderSetup(fragment, fragmentShader);

	m_shaderProg = glCreateProgram();
	glAttachShader(m_shaderProg, vertexShader);
	glAttachShader(m_shaderProg, geometryShader);
	glAttachShader(m_shaderProg, fragmentShader);
	glLinkProgram(m_shaderProg);

	glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		memset(buffer, 0, 1024);
		glGetProgramInfoLog(m_shaderProg, 1024, nullptr, buffer);
		logError("Error compiling shaders (vertexShader) {0}, (geometryShader) {1} and (fragmentShader) {2} ", vertex, geometry, fragment);
		logInfo(buffer);
		m_valid = false;
	}

	glDetachShader(m_shaderProg, vertexShader);
	glDetachShader(m_shaderProg, geometryShader);
	glDetachShader(m_shaderProg, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
	m_valid = true;

}


Shader::~Shader()
{
	glDeleteProgram(m_shaderProg);
}

void Shader::use()
{
	glUseProgram(m_shaderProg);
}

void Shader::unuse()
{
	glUseProgram(NULL);
}

//uniform mat3
void Shader::setMat3(std::string name, glm::mat3 mat)
{
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());

		if (uniformLoc == -1)
		{
			logError("Could not find uniform {0}", name);
			return;
		}
	glUniformMatrix3fv(uniformLoc, 1, GL_FALSE, &mat[0][0]);
}
//uniform mat4
void Shader::setMat4(std::string name, glm::mat4 mat)
{
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());

		if (uniformLoc == -1)
		{
			logError("Could not find uniform {0}", name);
			return;
		}

	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &mat[0][0]);
}
//uniform vec3
void Shader::setVec3(std::string name, glm::vec3 vec)
{
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());

		if (uniformLoc == -1)
		{
			logError("Could not find uniform {0}", name);
			return;
		}
	glUniform3fv(uniformLoc, 1, &vec[0]);
}
//uniform vec4
void Shader::setVec4(std::string name, glm::vec4 vec)
{
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());

		if (uniformLoc == -1)
		{
			logError("Could not find uniform {0}", name);
			return;
		}
	glUniform3fv(uniformLoc, 1, &vec[0]);

}
//uniform float
void Shader::setFloat(std::string name, float num)
{
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());

	if (uniformLoc == -1)
	{
		logError("Could not find uniform {0}", name);
		return;
	}

	glUniform1f(uniformLoc, num);

}
//uniform int
void Shader::setInt(std::string name, int num)
{
	GLint uniformLoc = glGetUniformLocation(this->getShaderID(), name.c_str());

	if (uniformLoc == -1)
	{
		logError("Could not find uniform {0}", name);
		return;
	}

	glUniform1i(uniformLoc, num);
}

bool Shader::getValid() const
{
	return m_valid;
}

int Shader::getShaderID() const
{
	return m_shaderProg;
}

void Shader::setName(std::string name)
{
	m_name = name;
}

void Shader::setMaterial(const Material& mat)
{
	setVec3("DiffuseCol", mat.diffuseCol);
}

void Shader::setMaterial(Material* mat)
{
	if (mat == nullptr) {
		return;
	}

	//setVec3("AmbientCol", mat->ambientCol);
	setVec3("DiffuseCol", mat->diffuseCol);
	if (mat->textures.size() > 0) {
		glBindTexture(GL_TEXTURE_2D, mat->textures.at(0));
	}
}

void Shader::direcionalLightData(const DirectionalLight& directionalLight)
{
	m_directionalLight = directionalLight;
}

void Shader::bindDirectionalLight()
{
	setVec3("directionalLight.direction", m_directionalLight.direction);
	setVec3("directionalLight.color", m_directionalLight.color);
	setFloat("directionalLight.ambientStrength", m_directionalLight.ambientStrength);
}

std::string Shader::getName() const
{
	return m_name;
}

std::vector<std::string> Shader::getShaderNames() const
{
	return m_shaderNames;
}

//one function for all the shaders instead of one for each
void Shader::shaderSetup(std::string shaderName, unsigned int& shader)
{
	std::string Code;
	std::ifstream Shader;
	Shader.open(SHADER_PATH + shaderName);

	if (!Shader.is_open())
	{
		logError("Failed to find shader file {0}", shaderName);
	}

	std::stringstream Stream;
	Stream << Shader.rdbuf();
	Shader.close();

	Code = Stream.str();

	GLint compileResult;
	char buffer[1024];

	const char* shaderPtr = Code.c_str();
	glShaderSource(shader, 1, &shaderPtr, nullptr);
	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	m_shaderNames.push_back(shaderName);

	if (compileResult == GL_FALSE)
	{
		glGetShaderInfoLog(shader, 1024, nullptr, buffer);
		logWarning("ERROR COMPILING: ");
		logWarning(shaderName);
		logInfo(buffer);
	}
}

Shader& Shader::operator=(const Shader& other) {

	if (&other == this) {
		return *this;
	}
	else {
		//Clear and remove the shader program
		glDeleteProgram(m_shaderProg);

		m_shaderProg = other.m_shaderProg;
		m_name = other.m_name;
		m_shaderNames = other.m_shaderNames;
		return *this;
	}
}