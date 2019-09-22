#ifndef _MESHLOADER_h
#define _MESHLOADER_h
#include <PCH/pch.h>
#include <Engine/GameObjects/Mesh.h>
#include <Engine/Materials/MaterialMap.h>

class MeshLoader {
public:
	std::vector<Mesh*> interpretMesh(std::string name);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene);

	//Returns the materialName
	std::string setupMaterial(aiMaterial* material, std::string type);
	//std::vector<Texture> loadTextures();

private:
	std::string directory;
	std::vector<Mesh*> m_meshes;
};

#endif // !_MESHLOADER_h
