#include "PCH/pch.h"
#include "UI.h"

const char* glsl_version = "#version 130";

UI::UI(GLFWwindow* window)
{
	//IMGUI
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	m_quit = false;
}

UI::~UI()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void UI::render()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Control Window
	{
		controlWindow();
	}
	//Light settings
	{
		lightSettings();
	}
	//Stats
	{
		stats();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::controlWindow()
{
	ImGui::Begin("Welcome To Chisel!");
	ImGui::SetWindowPos(ImVec2(0, 0));
	ImGui::SetWindowSize(ImVec2(400, 200));
	ImGui::Text("___Controls___");
	ImGui::Text("QUIT	( KEY : Escape )");
	ImGui::Text("Shader Hot Reload	( KEY : F1 )");
	ImGui::Checkbox("Wireframe mode	( KEY : TAB )", &m_wireFrameToggle);
	ImGui::Checkbox(" : FREE ROAM	( KEY : CTRL )", &m_cameraToggle);
	ImGui::End();
}

void UI::lightSettings()
{
	ImGui::Begin("Lights");
	ImGui::SetWindowPos(ImVec2(0, 250));
	ImGui::SetWindowSize(ImVec2(400, 200));
	if (ImGui::CollapsingHeader("Directional Light")) {
		ImGui::SliderFloat3("Direction", dirLight, -1.0f, 1.0f);
		ImGui::ColorEdit3("Color", dirLightColor);
		ImGui::SliderFloat("Ambient Strength", &m_ambientStrength, 0, 1);
	}

	if (ImGui::CollapsingHeader("Point Light")) {
		ImGui::SliderFloat3("Direction", m_pointLightPosition, -100, 100);
		ImGui::ColorEdit3("Color", m_pointLightColor);
		ImGui::Button("Place", ImVec2(50, 25));

	}
	ImGui::End();
}

void UI::stats()
{
	ImGui::Begin("Stats");
	ImGui::SetWindowPos(ImVec2(SCREEN_WIDTH * 2 - 400, 0));
	ImGui::SetWindowSize(ImVec2(400, 200));
	if (ImGui::CollapsingHeader("Statistics")) {
		std::string text = "FPS: " + std::to_string(m_frameRate);
		ImGui::BulletText(text.c_str());

		text = "Total Duplicate Textures: " + std::to_string(m_numberOfDuplicateTextures);
		ImGui::BulletText(text.c_str());
	}



	if (ImGui::Button("Quit")) {
		m_quit = true;
	}
	ImGui::End();
}
