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
	int m_frameRate;
	bool m_quit;
	//Directional Light related
	float dirLight[3] = { -.03f, -1.0f, 0.8f };				//Represents the direction of the light
	float dirLightColor[3] = { 1.0f, 1.0f, 1.0f };			//Represents directional light color
	float m_ambientStrength = 0.5f;							//Ambient light strength of the scene

	//Pointlight related
	float m_pointLightPosition[3] = { 1.0f, 1.0f, 1.0f };	//Represents Position
	float m_pointLightColor[3] = { 1.0f, 1.0f, 1.0f };		//Represents Color
	float m_pointLightStrRad[2] = { 1.0f, 1.0f };			//Represents strength and radius

	int m_numberOfDuplicateTextures;
private: //Private helpers
	void controlWindow();
	void lightSettings();
	void stats();
};