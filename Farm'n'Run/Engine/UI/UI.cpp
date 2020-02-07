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
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);	

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//Control Window
	//Requires Formatting 
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
	//World Settings
	{
		ImGui::Begin("World Settings");
		ImGui::SetWindowPos(ImVec2(0, 250));
		ImGui::SliderFloat3("Direction", dirLight, -1.0f, 1.0f);
		ImGui::ColorEdit3("Color", dirLightColor);

		ImGui::End();
	}


	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
}
