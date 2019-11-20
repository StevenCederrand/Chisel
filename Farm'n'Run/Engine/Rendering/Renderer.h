#ifndef _RENDERER_h
#define _RENDERER_h
#include <PCH/pch.h>
#include <Engine/GameObjects/GameObject.h>
#include <Engine/Materials/MaterialMap.h>
#include <Engine/Shaders/ShaderMap.h>
#include <Game/Camera/Camera.h>

struct RenderMatrix {
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};

class Renderer {
public:
	static Renderer* getInstance();
	//I should really only be submitting meshes!
	void submit(GameObject* gameObject, ObjectType objType);
	void submitCamera(Camera* renderMatrix);

	void destroy();

	

	void render();

private:
	Renderer();
	static Renderer* m_instance;
	Camera* m_camera;
	//RenderMatrix* m_renderMatrixes; //This pointer is to be deleted by the camera
	std::vector<GameObject*> m_staticObjects;
	std::vector<GameObject*> m_dynamicObjects;
	ShaderMap* m_shaderMap;

};


#endif