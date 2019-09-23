#include <PCH/pch.h>
#include "Renderer.h"

Renderer* Renderer::m_instance;

Renderer::Renderer() {
	
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
	}
	return m_instance;
}

void Renderer::destroy() {
	delete m_instance;
}
//Index based rendering
void Renderer::render(const RenderMatrix& renderMatrix, const GameObject& gameObject) {
	

	ShaderMap::getInstance()->getShader("Forward")->setMat4("prjMatrix", renderMatrix.projMatrix);
	ShaderMap::getInstance()->getShader("Forward")->setMat4("viewMatrix", renderMatrix.viewMatrix);
	ShaderMap::getInstance()->getShader("Forward")->setMat4("modelMatrix", gameObject.getModelMatrix());

	for (int i = 0; i < gameObject.getMesh().size(); i++) {
		std::string matName = gameObject.getMesh().at(i)->getMaterialName();

		if ( matName != "") {
			ShaderMap::getInstance()->getShader("Forward")->setMaterial(MaterialMap::getInstance()->getMaterial(matName));
		}

		glBindVertexArray(gameObject.getMesh().at(i)->getBuffers().m_VAO);
		glDrawElements(GL_TRIANGLES, gameObject.getMesh().at(i)->getNrOfIndices(), GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
	}


}


void Renderer::renderCube(RenderMatrix renderMatrix, GLuint VAO)
{
	ShaderMap::getInstance()->getShader("Forward")->setMat4("prjMatrix", renderMatrix.projMatrix);
	ShaderMap::getInstance()->getShader("Forward")->setMat4("viewMatrix", renderMatrix.viewMatrix);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}