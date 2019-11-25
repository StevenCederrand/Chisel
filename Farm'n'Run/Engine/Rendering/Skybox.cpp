#include <PCH/pch.h>
#include "Skybox.h"

Skybox::Skybox()
{
	loadSkybox();
}

Skybox::~Skybox()
{
	glDeleteVertexArrays(1, &m_skyboxData.m_vao);
	glDeleteBuffers(1, &m_skyboxData.m_vbo);
	glDeleteTextures(1, &m_skyboxData.m_textureID);
}

const SkyboxData& Skybox::getSkyboxData() const
{
	return m_skyboxData;
}

void Skybox::loadSkybox()
{

	glGenTextures(1, &m_skyboxData.m_textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skyboxData.m_textureID);
	int width, height, channels;
	unsigned char* data;
	std::string path;
	for (size_t i = 0; i < m_textures.size(); i++)
	{
		path = TEXTURE_PATH + m_textures.at(i);

		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			logError("Failed to load CUBEMAP texture {0}", m_textures.at(i));
			stbi_image_free(data);
			return;
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


	glGenVertexArrays(1, &m_skyboxData.m_vao);
	glGenBuffers(1, &m_skyboxData.m_vbo);

	glBindVertexArray(m_skyboxData.m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_skyboxData.m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);


}
