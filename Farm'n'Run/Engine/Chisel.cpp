#include "PCH/pch.h"
#include "Chisel.h"

Chisel* Chisel::m_chisel = 0;


Chisel::Chisel()
{
	m_shaderMap = ShaderMap::getInstance();
	m_shaderMap->createShader(SHADER_ID::FORWARD, "vShader.glsl", "fShader.glsl");
	m_shaderMap->createShader(SHADER_ID::SKYBOX, "SkyboxVS.glsl", "SkyboxFS.glsl");
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
