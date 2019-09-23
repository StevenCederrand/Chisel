#include <PCH/pch.h>
#include "Application.h"

Application::Application()
{
}

Application::~Application()
{
	delete m_cube;
	delete m_camera;
	Renderer::getInstance()->destroy();
	ShaderMap::getInstance()->destroy();
	MaterialMap::getInstance()->destroy();
	TextureMap::getInstance()->destroy();
	delete m_window;
	delete obj;
	delete obj2;
}

bool Application::init()
{
	m_window = new Window(1280, 720, "FarmNRun");

	return m_window->isActive();
}

void Application::update()
{

	m_cube = new PrimitiveCube();
	m_camera = new Camera();
	ShaderMap::getInstance()->createShader("Forward", "vShader.glsl", "fShader.glsl");

	float timeNow = 0.0f;
	float timeEnd = 0.0f;
	float deltaTime = 0.0f;

	//GameObject g_Object;
	MeshLoader mLoader;
	//GameObject g_Object2;
	obj = new GameObject();
	obj2 = new GameObject();
	obj->setMesh(mLoader.interpretMesh("cube.fbx"));
	obj2->setMesh(mLoader.interpretMesh("icoSphere.fbx"));

	obj->setWorldPosition(glm::vec3(0, 0, 0));
	obj2->setWorldPosition(glm::vec3(2, 1, 0));
	
	ShaderMap::getInstance()->useByName("Forward");
	///ShaderMap::getInstance()->getShader("Forward")->setInt("DiffuseTexture", 0);

	//While the window is active
	while (m_window->isActive()) {
		timeNow = static_cast<float>(glfwGetTime());

		m_window->clear();
		//Close the window
		if (Input::isKeyPressed(GLFW_KEY_ESCAPE)) {
			m_window->closeWindow();
		}

		m_camera->update(deltaTime);

		ShaderMap::getInstance()->useByName("Forward");
		Renderer::getInstance()->render(m_camera->getRenderMatrixes(), *obj);
		Renderer::getInstance()->render(m_camera->getRenderMatrixes(), *obj2);


		timeNow = static_cast<float>(glfwGetTime());
		deltaTime = timeNow - timeEnd;
		timeEnd = timeNow;


		m_window->swapBuffers();
	}
}
