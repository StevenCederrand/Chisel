#include "PCH/pch.h"
#include "Camera.h"

Camera::Camera()
{
	m_cameraPos = glm::vec3(0, 0, 3);
	m_worldUp = glm::vec3(0, 1, 0);
	m_cameraFace = glm::vec3(0, 0, -1);
	m_camYaw = -90.0f;
	m_camSpeed = 25;
	m_sensitivity = 0.15f;
	m_camPitch = 0;

	projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, NEAR_PLANE, FAR_PLANE);
	viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFace, m_worldUp);
}

Camera::~Camera()
{

}

void Camera::update(float deltaTime) {
	viewMatrix = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFace, m_worldUp);
	keys(deltaTime);
	mouseCallback();
}

void Camera::mouseCallback() {

	m_lastX = 640.0f;
	m_lastY = 360.0f;

	glfwGetCursorPos(glfwGetCurrentContext(), &m_posX, &m_posY);
	glfwSetCursorPos(glfwGetCurrentContext(), m_lastX, m_lastY);
	if (this->m_start == true)
	{
		this->m_start = false;
		m_posX = m_lastX;
		m_posY = m_lastY;
	}

	float xoffset = m_posX - m_lastX;
	float yoffset = m_lastY - m_posY;

	m_lastX = m_posX;
	m_lastY = m_posY;

	mouseControls(xoffset, yoffset, true);
}

const glm::mat4& Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

const glm::mat4& Camera::getViewMatrix() const
{
	return viewMatrix;
}

void Camera::mouseControls(float xOffset, float yOffset, bool pitchLimit) {
	xOffset *= m_sensitivity;
	yOffset *= m_sensitivity;

	m_camYaw += xOffset;
	m_camPitch += yOffset;

	if (pitchLimit)
	{
		if (m_camPitch > 89.0f)
			m_camPitch = 89.0f;
		if (m_camPitch < -89.0f)
			m_camPitch = -89.0f;
	}

	calcVectors();
}

void Camera::calcVectors()
{
	glm::vec3 face;
	face.x = cos(glm::radians(m_camYaw)) * cos(glm::radians(m_camPitch));
	face.y = sin(glm::radians(m_camPitch));
	face.z = sin(glm::radians(m_camYaw)) * cos(glm::radians(m_camPitch));

	m_cameraFace = glm::normalize(face);

	m_camerRight = glm::normalize(glm::cross(m_cameraFace, m_worldUp));
	m_cameraUp = glm::normalize(glm::cross(m_camerRight, m_cameraFace));
}


void Camera::keys(float deltaTime)
{
	if (Input::isKeyHeldDown(GLFW_KEY_W)) {
		m_cameraPos += m_cameraFace * deltaTime * m_camSpeed;
	}
	if (Input::isKeyHeldDown(GLFW_KEY_S)) {
		m_cameraPos -= m_cameraFace * deltaTime * m_camSpeed;
	}
	if (Input::isKeyHeldDown(GLFW_KEY_A)) {
		m_cameraPos -= m_camerRight * deltaTime * m_camSpeed;
	}
	if (Input::isKeyHeldDown(GLFW_KEY_D)) {
		m_cameraPos += m_camerRight * deltaTime * m_camSpeed;
	}
}

