#ifndef _SKYBOX_h
#define _SKYBOX_h
#include <PCH/pch.h>

struct SkyboxData {
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_textureID;
};

class Skybox {
public:
	Skybox();
	~Skybox();

	const SkyboxData& getSkyboxData() const;

private:
	void loadSkybox();
	
	std::vector<std::string> m_textures{
		"/Skybox/rt.png", 
		"/Skybox/lf.png",
		"/Skybox/up.png",
		"/Skybox/dn.png",
		"/Skybox/bk.png",
		"/Skybox/ft.png",
	};

	SkyboxData m_skyboxData;

	glm::vec3 skyboxVertices[36] = {
		// positions          
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		 glm::vec3(1.0f, -1.0f, -1.0f),
		 glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),

		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),

		 glm::vec3(1.0f, -1.0f, -1.0f),
		 glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		 glm::vec3(1.0f,  1.0f,  1.0f),
		 glm::vec3(1.0f,  1.0f, -1.0f),
		 glm::vec3(1.0f, -1.0f, -1.0f),

		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		 glm::vec3(1.0f,  1.0f,  1.0f),
		 glm::vec3(1.0f,  1.0f,  1.0f),
		 glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),

		glm::vec3(-1.0f,  1.0f, -1.0f),
		 glm::vec3(1.0f,  1.0f, -1.0f),
		 glm::vec3(1.0f,  1.0f,  1.0f),
		 glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),

		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		 glm::vec3(1.0f, -1.0f, -1.0f),
		 glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		 glm::vec3(1.0f, -1.0f,  1.0f)
	};
};


#endif