#include <PCH/pch.h>
#include "Application.h"

//DeltaTime 
namespace DeltaTime {

	float timeNow = 0.0f;
	float timeEnd = 0.0f;
	float deltaTime = 0.0f;

	void startDeltaTime() {
		timeNow = static_cast<float>(glfwGetTime());
	}

	//End the deltaTime 
	void endDeltaTime() {
		timeNow = static_cast<float>(glfwGetTime());
		deltaTime = timeNow - timeEnd;
		timeEnd = timeNow;
	}
}

Application::Application()
{
}

Application::~Application()
{
	delete m_camera;
	delete obj;
	Chisel::GetChisel()->destroy();
}

bool Application::init()
{
	m_window = new Window(1280, 720, "Chisel -- Engine");

	return m_window->isActive();
}

void Application::update()
{
	//Create a camera and 
	m_camera = new Camera();
	
	Chisel::GetChisel()->setCamera(m_camera);
	//Create and place the objects into a vector
	m_GO.emplace_back(new GameObject("thing", "thing.fbx", ObjectType::STATIC_OBJECT));
	m_GO.emplace_back(new GameObject("Ico", "icosphere.fbx", ObjectType::STATIC_OBJECT));

	m_GO[1]->setWorldPosition(glm::vec3(2, 0, 0));
	m_GO[0]->setRotation(glm::quat(glm::vec3(-1.7, 0, 0)));
	//While the window is active
	while (m_window->isActive()) {
		DeltaTime::startDeltaTime();

		m_window->clear();
		//Close the window
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
			m_window->closeWindow();
		}

		
		m_camera->update(DeltaTime::deltaTime);
		
		Chisel::GetChisel()->render();

		DeltaTime::endDeltaTime();
		m_window->swapBuffers();
	}
}
