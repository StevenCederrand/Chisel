#ifndef _APPLICATION_H
#define _APPLICATION_H
#include <PCH/pch.h>
#include <Engine/Window/Window.h>
#include <Engine/GameObjects/PrimitiveCube.h>
#include <Game/Camera/Camera.h>
#include <Engine/GameObjects/Gameobject.h>
#include <Engine/Utility/Loader/MeshLoader.h>

class Application {
public: 
	Application();
	~Application();

	bool init();

	void update();




private:
	Camera* m_camera;
	PrimitiveCube* m_cube;
	Window* m_window;
};



#endif