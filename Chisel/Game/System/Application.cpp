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
	Chisel::GetChisel()->destroy();
}

bool Application::init()
{
	Chisel::GetChisel();
	return true; //Return an init of chisel
}

void Application::update()
{
	//Create a camera and 
	//Create and place the objects into a vector
	m_GO.emplace_back(new GameObject("Sponza", "sponza.obj", ObjectType::STATIC_OBJECT));
	m_GO[0]->setScale(glm::vec3(0.01f));
	
	m_GO.emplace_back(new GameObject("cubes", "cube.obj", ObjectType::STATIC_OBJECT));
	m_GO[1]->setScale(glm::vec3(0.1f));

	m_GO.emplace_back(new GameObject("cubes2", "cube0.obj", ObjectType::STATIC_OBJECT));
	m_GO[2]->setScale(glm::vec3(0.1f));
	m_GO[2]->setPosition(glm::vec3(1, 1, 0));
	

	Chisel::GetChisel()->setDuplicateCount(TextureMap::getInstance()->totalNumberOfDuplicates());

	//While the window is active
	while (Chisel::GetChisel()->isActive()) {
		DeltaTime::startDeltaTime();

		Chisel::GetChisel()->update(DeltaTime::deltaTime);
		
		generalHandle();

		Chisel::GetChisel()->render();
		
		DeltaTime::endDeltaTime();
	}
}

void Application::generalHandle() {
	if (Input::isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
		Chisel::GetChisel()->toggleFreeRoam();
	}

	if (Input::isKeyPressed(GLFW_KEY_TAB)) {
		Chisel::GetChisel()->toggleWireframe();
	}

	//Close the window
	if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
		Chisel::GetChisel()->close();
	}

	if (Input::isKeyPressed(GLFW_KEY_F1)) {
		ShaderMap::getInstance()->reload();
	}
}
