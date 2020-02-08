#include "PCH/pch.h"
#include "Chisel.h"

Chisel* Chisel::m_chisel = 0;


Chisel::Chisel()
{
	m_window = new Window(1280 * 2, 720 * 2, "Chisel -- Engine");
	//ShaderMap setup
	{
		m_shaderMap = ShaderMap::getInstance();
		m_shaderMap->createShader(SHADER_ID::FORWARD, "vShader.glsl", "fShader.glsl");
		m_shaderMap->createShader(SHADER_ID::SKYBOX, "SkyboxVS.glsl", "SkyboxFS.glsl");
		m_directionalLight.direction = glm::vec3(-.03f, -1.0f, 0.8f);
		m_directionalLight.color = glm::vec3(1);
		ShaderMap::getInstance()->getShader(SHADER_ID::FORWARD)->direcionalLightData(m_directionalLight);
	}


	m_renderer = Renderer::getInstance();
	m_camera = new Camera();
	m_renderer->submitCamera(m_camera);
	m_ui = new UI(m_window->getWindow());
	
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
	delete m_camera;
	delete m_ui;
	delete m_window;
	delete m_chisel;
}

void Chisel::update(const float& dt)
{
	calculateFPS(dt);
	m_camera->update(dt);

	if (m_camera->getLock() != m_ui->m_cameraToggle) {
		toggleFreeRoam();
	}

	if (m_renderer->getWireframe() != m_ui->m_wireFrameToggle) {
		toggleWireframe();
	}

	//Directional Light
	{
		//Assign directional value
		if (m_ui->dirLight[0] != m_directionalLight.direction.x || m_ui->dirLight[1] != m_directionalLight.direction.y ||
			m_ui->dirLight[2] != m_directionalLight.direction.z) {
			//Assign the direction
			m_directionalLight.direction = glm::vec3(m_ui->dirLight[0], m_ui->dirLight[1], m_ui->dirLight[2]);
			ShaderMap::getInstance()->getShader(SHADER_ID::FORWARD)->direcionalLightData(m_directionalLight);
		}
		//Assign color value
		if (m_ui->dirLightColor[0] != m_directionalLight.direction.x || m_ui->dirLightColor[1] != m_directionalLight.color.y ||
			m_ui->dirLightColor[2] != m_directionalLight.direction.z) {
			//Assign the color
			m_directionalLight.color = glm::vec3(m_ui->dirLightColor[0], m_ui->dirLightColor[1], m_ui->dirLightColor[2]);
			ShaderMap::getInstance()->getShader(SHADER_ID::FORWARD)->direcionalLightData(m_directionalLight);
		}
	}

	if (m_ui->m_quit) {
		m_window->closeWindow();
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

void Chisel::calculateFPS(const float& dt) {
	static unsigned fps = 0;
	static float frameTimer = 1.0f;
	fps++;
	frameTimer -= dt;
	if (frameTimer <= 0.0f)
	{
		frameTimer = 1.0f;
		m_ui->m_frameRate = fps;
		fps = 0;
	}
}