#ifndef _CAMERA_h
#define _CAMERA_h
#include <PCH/pch.h>
#include <Engine/Rendering/Renderer.h>
#include <Engine/Utility/Input.h>

#define NEAR_PLANE 0.01f
#define FAR_PLANE 200.0f

class Camera {
public:
	Camera();
	~Camera();

	void update(float deltaTime);
	void keys(float deltaTime);
	const RenderMatrix& getRenderMatrixes() const;
	void mouseCallback();
private:
	RenderMatrix m_matrixes;
	
	void mouseControls(float xOffset, float yOffset, bool pitchLimit);
	void calcVectors();

	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFace;
	glm::vec3 m_worldUp;
	glm::vec3 m_cameraUp;
	glm::vec3 m_camerRight;
	
	float m_camYaw;
	float m_camSpeed;
	float m_camPitch;
	float m_sensitivity;
	float m_lastX;
	float m_lastY;
	double m_posX;
	double m_posY;
	bool m_start = true;
};


#endif // !_CAMERA_h
