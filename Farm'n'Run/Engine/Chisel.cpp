#include "PCH/pch.h"
#include "Chisel.h"

Chisel* Chisel::m_chisel = 0;


Chisel::Chisel()
{
	m_window = new Window(1280 * 2, 720 * 2, "Chisel -- Engine");

	m_shaderMap = ShaderMap::getInstance();
	m_shaderMap->createShader(SHADER_ID::FORWARD, "vShader.glsl", "fShader.glsl");
	m_shaderMap->createShader(SHADER_ID::SKYBOX, "SkyboxVS.glsl", "SkyboxFS.glsl");
	m_renderer = Renderer::getInstance();

#pragma region UI
	m_ui = new UI(m_window->getWindow());
#pragma endregion
}

Chisel* Chisel::GetChisel()
{
	if (m_chisel == nullptr) {
		m_chisel = new Chisel();
	}
	return m_chisel;
}

void Chisel::setCamera(Camera* camera)
{
	m_camera = camera;
	m_renderer->submitCamera(camera);
	m_ui->m_cameraToggle = m_camera->getLock();
}

//Careful when invoking this function. It will destroy chisel
void Chisel::destroy()
{
	Renderer::getInstance()->destroy();
	ShaderMap::getInstance()->destroy();
	MaterialMap::getInstance()->destroy();
	TextureMap::getInstance()->destroy();
	delete m_ui;
	delete m_window;
	delete m_chisel;
}

void Chisel::update()
{
	if (m_camera->getLock() != m_ui->m_cameraToggle) {
		toggleFreeRoam();
	}

	if (m_renderer->getWireframe() != m_ui->m_wireFrameToggle) {
		toggleWireframe();
	}
}


void Chisel::render()
{
	m_window->clear();
	m_renderer->render();
	m_ui->render();
	m_window->swapBuffers();
}

bool Chisel::isActive()
{
	return m_window->isActive();
}

void Chisel::close()
{
	m_window->closeWindow();
}

void Chisel::toggleFreeRoam()
{
	m_ui->m_cameraToggle = m_camera->lockCamera();
}

void Chisel::toggleWireframe()
{
	m_ui->m_wireFrameToggle = m_renderer->setWireframe();
}
