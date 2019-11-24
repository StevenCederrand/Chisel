#include "PCH/pch.h"
#include "PrimitiveCube.h"

PrimitiveCube::PrimitiveCube()
{
	float vertices[] = {
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f,

		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,

		-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  1.0f, 0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, 1.0f,

		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,
		 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f
	};

	m_worldPos = glm::vec3(0.0f, 0.0f, 0.0f);

	glGenVertexArrays(1, &m_buffers.VAO);
	glGenBuffers(1, &m_buffers.VBO);


	glBindVertexArray(m_buffers.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffers.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	m_worldPos = glm::vec3(0, 0, 0);
	m_modelMatrix = glm::mat4(1);
	m_buffers.sizeOfData = 36;
}

PrimitiveCube::~PrimitiveCube()
{
	glDeleteVertexArrays(1, &m_buffers.VAO);
	glDeleteBuffers(1, &m_buffers.VBO);
}

//The texture path is automatically placed onto the name
void PrimitiveCube::loadTexture(std::string textureName) {
	textureName = TEXTURE_PATH + textureName;

	GLuint m_textureID;
	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrOfChannels;
	unsigned char* data = stbi_load(textureName.c_str(), &width, &height, &nrOfChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		logError("Failed to load texture");
	}

	stbi_image_free(data);
}

//Assumes that the shader that the texture is to be bound to is currently "used"
void PrimitiveCube::bindTextures(Shader* currentShader) {
	currentShader->setInt("albedoTexture", 1);
}

const GLuint& PrimitiveCube::getVAO() const
{
	return m_buffers.VAO;
}

const glm::vec3& PrimitiveCube::getWorldPos() const {
	return m_worldPos;
}

const glm::mat4& PrimitiveCube::getModelMatrix() const {
	return glm::translate(m_modelMatrix, m_worldPos);
}
const GLuint& PrimitiveCube::getTextureID() const {
	return m_textureID;
}

const Buffer& PrimitiveCube::getBuffers() const
{
	return m_buffers;
}
