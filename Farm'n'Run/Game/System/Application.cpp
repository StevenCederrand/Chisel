#include <PCH/pch.h>
#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
	delete m_camera;
	delete m_window;
	delete obj;
	Chisel::GetChisel()->destroy();
}

bool Application::init()
{
	m_window = new Window(1280, 720, "FarmNRun");

	return m_window->isActive();
}

void Application::update()
{
	m_camera = new Camera();
	
	Chisel::GetChisel()->createShader();
	Chisel::GetChisel()->setCamera(m_camera);


	float timeNow = 0.0f;
	float timeEnd = 0.0f;
	float deltaTime = 0.0f;

	m_GO.push_back(new GameObject("Cube", "cube.fbx", 1));
	m_GO.push_back(new GameObject("Ico", "icosphere.fbx", 1));

	m_GO[1]->setWorldPosition(glm::vec3(0, 2, 0));
	
	//While the window is active
	while (m_window->isActive()) {
		timeNow = static_cast<float>(glfwGetTime());

		m_window->clear();
		//Close the window
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
			m_window->closeWindow();
		}

		m_camera->update(deltaTime);

		timeNow = static_cast<float>(glfwGetTime());
		deltaTime = timeNow - timeEnd;
		timeEnd = timeNow;

		Chisel::GetChisel()->render();

		m_window->swapBuffers();
	}
}
