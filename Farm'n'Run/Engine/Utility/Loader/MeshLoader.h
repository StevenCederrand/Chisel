#ifndef _MESHLOADER_h
#define _MESHLOADER_h
#include <PCH/pch.h>
#include <Engine/GameObjects/Mesh.h>
#include <Engine/Materials/MaterialMap.h>
#include <Engine/Textures/TextureMap.h>
class MeshLoader {
public:

	~MeshLoader();

	std::vector<Mesh*> interpretMesh(std::string name);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& mesh);

	//Returns the materialName
	Material* loadMaterial(aiMaterial* material);
	void loadTextures(aiMaterial* material, aiTextureType textureType, Material* engineMat, const std::string& type);

	TextureMap* m_textureMap;
};

#endif // !_MESHLOADER_h
