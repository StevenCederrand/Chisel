#include "PCH/pch.h"
#include "Chisel.h"

Chisel* Chisel::m_chisel = 0;


Chisel::Chisel()
{
	ShaderMap::getInstance()->createShader(SHADER_ID::Forward, "vShader.glsl", "fShader.glsl");
}

Chisel* Chisel::GetChisel()
{
	if (m_chisel == nullptr) {
		m_chisel = new Chisel();
	}
	return m_chisel;
}

void Chisel::setCamera(Camera* camera)
{
	Renderer::getInstance()->submitCamera(camera);
}

//Careful when invoking this function. It will destroy chisel
void Chisel::destroy()
{
	Renderer::getInstance()->destroy();
	ShaderMap::getInstance()->destroy();
	MaterialMap::getInstance()->destroy();
	TextureMap::getInstance()->destroy();

	delete m_chisel;
}

void Chisel::render()
{
	Renderer::getInstance()->render();
}
