#ifndef _CHISEL_h
#define _CHISEL_h
#include <PCH/pch.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Window/Window.h>
#include <Engine/UI/UI.h>
#include <Game/Camera/Camera.h> 

class Chisel {
public:
	Chisel();
	

	static Chisel* GetChisel();
		
	void setCamera(Camera* camera);
	
	void destroy();
	void update(const float& dt);
	void render();
	
	bool isActive();
	void close();

	void toggleFreeRoam();
	void toggleWireframe();

	void calculateFPS(const float& dt);
private:
	static Chisel* m_chisel;
	ShaderMap* m_shaderMap;
	Renderer* m_renderer;
	Window* m_window;
	Camera* m_camera;
	UI* m_ui;

	DirectionalLight m_directionalLight;

	
};




#endif