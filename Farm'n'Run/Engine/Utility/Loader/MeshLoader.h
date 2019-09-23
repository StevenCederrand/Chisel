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
	std::string setupMaterial(aiMaterial* material);
	void loadTextures(aiMaterial* material, aiTextureType textureType, Material& engineMat, const std::string& type);

};

#endif // !_MESHLOADER_h
