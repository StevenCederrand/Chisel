#ifndef _RENDERER_h
#define _RENDERER_h
#include <PCH/pch.h>
#include <Engine/GameObjects/GameObject.h>
#include <Engine/Materials/MaterialMap.h>

struct RenderMatrix {
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
};



class Renderer {
public:
	static Renderer* getInstance();
	void destroy();

	//void render(GLuint VAO, int nrOfIndices);
	void renderCube(RenderMatrix renderMatrix, GLuint VAO);
	void render(const RenderMatrix& renderMatrix, const GameObject& gameObject);

private:
	Renderer();
	static Renderer* m_instance;
};


#endif