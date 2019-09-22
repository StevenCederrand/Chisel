#ifndef _PRIMITIVECUBE_h
#define _PRIMITIVECUBE_h

struct Buffer {
	GLuint VBO;
	GLuint VAO;
	GLuint IBO;
	int sizeOfData;
	int indicesCount;
};



class PrimitiveCube {
public:
	PrimitiveCube();
	~PrimitiveCube();

	void loadTexture(std::string textureName);

	const GLuint& getVAO() const;
	const glm::vec3& getWorldPos() const;
	const glm::mat4& getModelMatrix() const;
	const GLuint& getTextureID() const;
	const Buffer& getBuffers() const;

	void bindTextures(Shader* currentShader);
private:
	Buffer m_buffers;

	GLuint m_VAO;
	glm::vec3 m_worldPos;
	glm::mat4 m_modelMatrix;
	GLuint m_textureID;


};


#endif