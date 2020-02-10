#ifndef _WINDOW_h
#define _WINDOW_h
#include <PCH/pch.h>
#include <Engine/Rendering/Renderer.h>

class Window {
public: 

	Window(int width, int height, std::string windowHint);
	~Window();

	GLFWwindow* getWindow();
	const bool& isActive();

	void clear();
	void swapBuffers();
	void closeWindow();

private:
	GLFWwindow* m_window;
	Input* m_input;
	bool m_active;
};


#endif 