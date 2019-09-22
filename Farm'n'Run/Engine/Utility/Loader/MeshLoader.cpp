#include "PCH/pch.h"
#include "MeshLoader.h"

//MESH_PATH is added to the path automatically
std::vector<Mesh*> MeshLoader::interpretMesh(std::string name)
{
	Assimp::Importer importer;
	
	const aiScene* scene = importer.ReadFile(MESH_PATH + name, aiProcess_Triangulate | aiProcess_FlipUVs);
	std::vector<Mesh*> meshes;
	//If scene fails
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return meshes;
	}

	processNode(scene->mRootNode, scene);

	return m_meshes;
}


void MeshLoader::processNode(aiNode* node, const aiScene* scene) {

	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}

Mesh* MeshLoader::processMesh(aiMesh* mesh, const aiScene* scene)
{
	
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	bool hasTextureCoordinate = mesh->mTextureCoords[0];

	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vert;
		glm::vec3 vec3Data;

		vec3Data.x = mesh->mVertices[i].x;
		vec3Data.y = mesh->mVertices[i].y;
		vec3Data.z = mesh->mVertices[i].z;
		vert.position = vec3Data;

		vec3Data.x = mesh->mNormals[i].x;
		vec3Data.y = mesh->mNormals[i].y;
		vec3Data.z = mesh->mNormals[i].z;
		vert.normal = vec3Data;

		if (hasTextureCoordinate) {
			vec3Data.x = mesh->mTextureCoords[0][i].x;
			vec3Data.y = mesh->mTextureCoords[0][i].y;
			vert.uv = vec3Data;
		}
		else {
			vert.uv = glm::vec2(0, 0);
		}
		vertices.push_back(vert);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	std::string matName = "";
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		matName = setupMaterial(material, "Blandk");

	}
	

	Mesh* l_mesh = new Mesh(vertices, indices, matName);
	return l_mesh;
}

std::string MeshLoader::setupMaterial(aiMaterial* material, std::string type) {
	
	Material mat;
	std::vector<std::string> texturePaths;
	aiColor3D col;
	aiString name;

	
	material->Get(AI_MATKEY_NAME, name);
	material->Get(AI_MATKEY_COLOR_DIFFUSE, col);

	
	mat.diffuseCol = glm::vec3(col.r, col.g, col.b);
	
	

	MaterialMap::getInstance()->insertMat(name.C_Str(), mat, texturePaths);
	return name.C_Str();

}

/*
std::vector<Texture> MeshLoader::loadTextures(aiMaterial* material, aiTextureType, std::string type)
{
	
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture;
		texture.id = TextureFromFile(str.C_Str(), directory);
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);
	}
	return textures;	
}*/