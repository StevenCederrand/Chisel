#include <PCH/pch.h>
#include "Renderer.h"

Renderer* Renderer::m_instance;

Renderer::Renderer() {
	m_shaderMap = ShaderMap::getInstance();
	//Setup a basic directional light
	m_directionalLight.color = glm::vec3(1, 1, 1);
	m_directionalLight.direction = glm::vec3(0, -1, 0);

#if USING_SKYBOX
	initSkybox();
#endif
}

Renderer::~Renderer() {
#if USING_SKYBOX
	delete m_skybox;
#endif
}
void Renderer::initSkybox()
{
	m_skybox = new Skybox();
}

void Renderer::bindMatrixes(Shader* shader) {
	shader->setMat4("prjMatrix", m_camera->getProjectionMatrix());
	shader->setMat4("viewMatrix", m_camera->getViewMatrix());
}

Renderer* Renderer::getInstance() {
	if (m_instance == NULL) {
		m_instance = new Renderer();
		//Init GL rendering 
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_MULTISAMPLE);

		
	}
	return m_instance;
}

void Renderer::submit(GameObject* gameObject, ObjectType objType)
{
	if (objType == ObjectType::STATIC_OBJECT) {
		m_staticObjects.emplace_back(gameObject);
	}

}

void Renderer::submitCamera(Camera* camera)
{
	m_camera = camera;
}

void Renderer::destroy() {

	delete m_instance;
}

void Renderer::update() {
	
	//The renderer should be able to place out pointlights 
	if (Input::isKeyPressed(GLFW_KEY_SPACE)) {
		//Place a pointlight and hand it over so that we can render using it
		Pointlight pl;
		pl.position = glm::vec4(m_camera->getPosition(), 5.0f);		
		m_pointlights.push_back(pl);
	}

}

void Renderer::render()
{
	Shader* shader;

	if (m_staticObjects.size() <= 0) {

	}
	else {
		shader = m_shaderMap->useByName(SHADER_ID::FORWARD);

		bindMatrixes(shader);
		
		//If tab and wireframe off
		if (m_wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
		}

		shader->bindDirectionalLight();

		for (size_t i = 0; i < m_pointlights.size(); i++)
		{
			//shader->setVec4("")
		}

		for (size_t i = 0; i < m_staticObjects.size(); i++) {

			shader->setMat4("modelMatrix", m_staticObjects.at(i)->getTransform().matrix);
			std::vector<Mesh*> meshes = m_staticObjects.at(i)->getMesh();
			Mesh* mesh = nullptr;

			for (size_t j = 0; j < meshes.size(); j++) {
				mesh = meshes.at(j);

				//Optimze this by having the mesh hold a pointer to it's material/s
				Material* mat = mesh->getMaterialAt(0);
				shader->setMaterial(mat);

				glBindVertexArray(mesh->getBuffers().m_VAO);
				glDrawElements(GL_TRIANGLES, mesh->getNrOfIndices(), GL_UNSIGNED_INT, NULL);
				glBindTexture(GL_TEXTURE_2D, 0);
				glBindVertexArray(0);
			}
		}
	}

	/* If the setting for using a skybox is enabled */
#if USING_SKYBOX 
	glDepthFunc(GL_LEQUAL);
	glDepthMask(false);
	shader = m_shaderMap->useByName(SHADER_ID::SKYBOX);
	shader->setMat4("prjMatrix", m_camera->getProjectionMatrix());
	shader->setMat4("viewMatrix", glm::mat4(glm::mat3(m_camera->getViewMatrix()))); //Remove all use of the final row and column
	
	glBindVertexArray(m_skybox->getSkyboxData().m_vao);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_skybox->getSkyboxData().m_textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(true);
	glDepthFunc(GL_LESS);
#endif

}

DirectionalLight& Renderer::getDirectionalLight()
{
	return m_directionalLight;
}

bool Renderer::setWireframe()
{
	m_wireframe = !m_wireframe;
	return m_wireframe;
}

bool Renderer::getWireframe()
{
	return m_wireframe;
}
