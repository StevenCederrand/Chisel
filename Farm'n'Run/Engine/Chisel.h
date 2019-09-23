#ifndef _CHISEL_h
#define _CHISEL_h
#include <PCH/pch.h>
#include <Engine/Rendering/Renderer.h>
#include <Game/Camera/Camera.h> //Change this!!!!!

class Chisel {
public:
	Chisel();
	

	static Chisel* GetChisel();
	
	//Create a default shader
	void createShader();
	
	void setCamera(Camera* camera);

	void chiselSubmit(GameObject* gameObject, int objType);

	void destroy();
	void render();

private:
	static Chisel* m_chisel;
	

};




#endif