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
	for (size_t i = 0; i < m_GO.size(); i++)
	{
		delete m_GO[i];
	}
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
	m_GO.emplace_back(new GameObject("gun", "gun.fbx", ObjectType::STATIC_OBJECT));
	m_GO[0]->setScale(glm::vec3(0.05f));
	m_GO[0]->setPosition(glm::vec3(0, 0, 0));
	m_GO[0]->setRotation(glm::quat(glm::vec3(xRotation, 0, 0)));


	//While the window is active
	while (m_window->isActive()) {
		DeltaTime::startDeltaTime();

		m_window->clear();
		//Close the window
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
			m_window->closeWindow();
		}

		if (Input::isKeyHeldDown(GLFW_KEY_I)) {
			xRotation += 0.1f;
			m_GO[0]->setRotation(glm::quat(glm::vec3(xRotation, 0, 0)));
		}
		else if (Input::isKeyHeldDown(GLFW_KEY_K)) {
			xRotation -= 0.1f;
			m_GO[0]->setRotation(glm::quat(glm::vec3(xRotation, 0, 0)));
		}

		if (Input::isKeyPressed(GLFW_KEY_F1)) {
			ShaderMap::getInstance()->reload();
		}
		
		m_camera->update(DeltaTime::deltaTime);
		
		Chisel::GetChisel()->render();

		DeltaTime::endDeltaTime();
		m_window->swapBuffers();
	}
}
