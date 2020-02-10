#ifndef _MESH_h
#define _MESH_h
#include <PCH/pch.h>
#include <Engine/Materials/MaterialMap.h>


struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct RenderBuffers {
	GLuint m_VBO;
	GLuint m_IBO;
	GLuint m_VAO;
	int m_indices;
};



class Mesh {
public:

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

	//Adds the material to the list of materials
	void addMaterial(Material* mat);

	const RenderBuffers& getBuffers() const;

	int getNrOfIndices();
	const std::string& getMaterialName() const;
	Material* getMaterialAt(const int& i);

	const std::vector<Material*>& getMaterials() const;

private:
	RenderBuffers m_renderBuffers;
	
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::string m_materialName;
	std::vector<Material*> m_materials; 

	void setupMesh();
};



#endif 