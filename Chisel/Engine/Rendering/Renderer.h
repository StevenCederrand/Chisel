#ifndef _RENDERER_h
#define _RENDERER_h
#include <PCH/pch.h>
#include <Engine/GameObjects/GameObject.h>
#include <Engine/GameObjects/Lights.h>
#include <Engine/Materials/MaterialMap.h>
#include <Engine/Shaders/ShaderMap.h>
#include <Engine/Rendering/Skybox.h>
#include <Engine/Settings/Settings.h>
#include <Game/Camera/Camera.h>

struct RenderMatrix {
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};

struct Pointlight {
	glm::vec4 colour; // R, G, B & strength
	glm::vec4 position;// X, Y, Z & radius
	glm::vec3 attenuation;

	Pointlight() {
		colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		position = glm::vec4(0.0f, 0.0f, 0.0f, 5.0f);
		attenuation = glm::vec3(1.0f, 0.09f, 0.032f);
	}
};

class Renderer {
public: /* Functions */
	static Renderer* getInstance();
	//I should really only be submitting meshes!
	void submit(GameObject* gameObject, ObjectType objType);
	void submitCamera(Camera* camera);

	void destroy();
	void update(); //
	void render();

	DirectionalLight& getDirectionalLight();
	bool setWireframe();
	bool getWireframe();
private: 
	Renderer();
	~Renderer();

	void initSkybox();
	void bindMatrixes(Shader* shader); //Used to bind the view- and projection matrix

private: 
	static Renderer* m_instance;
	Camera* m_camera;
	Skybox* m_skybox;
	
	//RenderMatrix* m_renderMatrixes; //This pointer is to be deleted by the camera
	std::vector<GameObject*> m_staticObjects;
	std::vector<Pointlight> m_pointlights;

	ShaderMap* m_shaderMap;
	bool m_wireframe;

	DirectionalLight m_directionalLight;

};


#endif