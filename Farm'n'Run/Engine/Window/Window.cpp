#include "PCH/pch.h"
#include "Window.h"
#define STB_IMAGE_IMPLEMENTATION

Window::Window(int width, int height, std::string windowHint)
{
	bool statusOK = false;

	statusOK = glfwInit();

	if (!statusOK) {
		logError("Failed to initialize GLFW!");
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	m_window = glfwCreateWindow(width, height, windowHint.c_str(), NULL, NULL);

	if (m_window == nullptr) {
		glfwTerminate();
		logError("Failed to create GLFW window");
		return;
	}

	// Opengl context
	glfwMakeContextCurrent(m_window);

	GLenum status = glewInit();

	if (status != GLEW_OK) {
		glfwTerminate();
		logError("Failed to initialize GLEW!");
	}

	// Vsync --- Set to 60fps
	glfwSwapInterval(1);

	logTrace("Application successfully initialized");


	m_input = new Input();
	Renderer::getInstance(); //Create a rendering instance

	m_active = true;
}

Window::~Window()
{
	delete m_input;
}

GLFWwindow* Window::getWindow()
{
	return m_window;
}

const bool& Window::isActive()
{
	if (glfwWindowShouldClose(m_window)) {
		m_active = false;
	}
	return m_active;
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	m_input->clearKeys();
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

void Window::closeWindow()
{
	glfwSetWindowShouldClose(m_window, true);
	m_active = false;
}
