#ifndef _APPLICATION_H
#define _APPLICATION_H
#include <PCH/pch.h>
#include <Engine/Window/Window.h>
#include <Game/Camera/Camera.h>
#include <Engine/GameObjects/Gameobject.h>

class Application {
public: 
	Application();
	~Application();

	bool init();
	void update();
private:
	void generalHandle();

private:
	std::vector<GameObject*> m_GO;
	float xRotation = 4.6f;
};

#endif