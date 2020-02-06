#pragma once
#include <PCH/pch.h>
#include <Imgui/imgui.h>
#include <Imgui/imgui_impl_glfw.h>
#include <Imgui/imgui_impl_opengl3.h>

//A UI class for handling IMGUI
class UI {
public:
	UI(GLFWwindow* window);
	~UI();
	void render();

	bool m_cameraToggle;
	bool m_wireFrameToggle;

	float dirLight[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
};