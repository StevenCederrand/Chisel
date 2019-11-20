#include "PCH/pch.h"
#include "MeshLoader.h"

MeshLoader::~MeshLoader() {

}


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

	processNode(scene->mRootNode, scene, meshes);
	
	return meshes;
}


void MeshLoader::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>& meshes) {

	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, meshes);
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
		matName = setupMaterial(material);
	}
	

	Mesh* l_mesh = new Mesh(vertices, indices, matName);
	return l_mesh;
}

std::string MeshLoader::setupMaterial(aiMaterial* material) {
	
	Material mat;
	std::vector<std::string> texturePaths;
	aiColor3D col;
	aiString name;

	
	material->Get(AI_MATKEY_NAME, name);
	
	material->Get(AI_MATKEY_COLOR_DIFFUSE, col);
	mat.diffuseCol = glm::vec3(col.r, col.g, col.b);

	material->Get(AI_MATKEY_COLOR_AMBIENT, col);
	mat.ambientCol = glm::vec3(col.r, col.g, col.b);

	material->Get(AI_MATKEY_COLOR_SPECULAR, col);
	mat.specCol = glm::vec3(col.r, col.g, col.b);
	
 	loadTextures(material, aiTextureType_DIFFUSE, mat, "Diffuse");
		

	MaterialMap::getInstance()->insertMat(name.C_Str(), mat);
	return name.C_Str();

}

void MeshLoader::loadTextures(aiMaterial* material, aiTextureType textureType, Material& engineMat, const std::string& type)
{

	std::pair<std::string, std::string> matTexture; //Name of the texture and the type of texture that it is
	
	for (unsigned int i = 0; i < material->GetTextureCount(textureType); i++) {
		aiString str;
		std::string rString;
		material->GetTexture(textureType, i, &str); //Get the path for the texture. 
		


		rString = str.C_Str();

		//std::cout << << std::endl;
		matTexture.first = rString.substr(rString.find_last_of("\\/") + 1, rString.length());
		matTexture.second = type;  //Set the type for every texture

		logInfo(matTexture.first);
		//When we have determined the texture path, and the texture type.. 
		//Insert it into the texture map
		//TextureMap::getInstance()->insert(matTexture.first, rString, matTexture.second);

		//Then insert the pair into the material 
		//engineMat.textures.push_back(matTexture);
	}


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