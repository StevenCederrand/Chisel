#include <PCH/pch.h>
#include "Renderer.h"

Renderer* Renderer::m_instance;

Renderer::Renderer() {
	m_shaderMap = ShaderMap::getInstance();
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

void Renderer::render()
{
#if USING_SKYBOX //Skybox rendering
	
#endif
	Shader* shader;
	shader = m_shaderMap->useByName(SHADER_ID::Forward);

	shader->setMat4("prjMatrix", m_camera->getProjectionMatrix());
	shader->setMat4("viewMatrix", m_camera->getViewMatrix());

	//If tab and wireframe off
	if (Input::isKeyPressed(GLFW_KEY_TAB) && !m_wireframe) {
		m_wireframe = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if(Input::isKeyPressed(GLFW_KEY_TAB) && m_wireframe){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
		m_wireframe = false;
	}

	for (int i = 0; i < m_staticObjects.size(); i++) {
		shader->setMat4("modelMatrix", m_staticObjects.at(i)->getTransform().matrix);

		for (int j = 0; j < m_staticObjects.at(i)->getMesh().size(); j++) {

			std::string matName = m_staticObjects.at(i)->getMesh().at(j)->getMaterialName();
			shader->setMaterial(MaterialMap::getInstance()->getMaterial(matName));

			glBindVertexArray(m_staticObjects.at(i)->getMesh().at(j)->getBuffers().m_VAO);
			glDrawElements(GL_TRIANGLES, m_staticObjects.at(i)->getMesh().at(j)->getNrOfIndices(), GL_UNSIGNED_INT, NULL);
			glBindVertexArray(0);
		}
	}
}