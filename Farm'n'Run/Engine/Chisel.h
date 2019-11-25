#ifndef _CHISEL_h
#define _CHISEL_h
#include <PCH/pch.h>
#include <Engine/Rendering/Renderer.h>
#include <Game/Camera/Camera.h> //Change this!!!!!

class Chisel {
public:
	Chisel();
	

	static Chisel* GetChisel();
		
	void setCamera(Camera* camera);
	
	void destroy();
	void render();

private:
	static Chisel* m_chisel;
	ShaderMap* m_shaderMap;

};




#endif