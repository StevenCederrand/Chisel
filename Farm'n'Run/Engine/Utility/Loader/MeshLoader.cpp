#include "PCH/pch.h"
#include "MeshLoader.h"

MeshLoader::~MeshLoader() {

}


//MESH_PATH is added to the path automatically
std::vector<Mesh*> MeshLoader::interpretMesh(std::string name)
{
	Assimp::Importer importer;
	m_textureMap = TextureMap::getInstance();

	unsigned int importOptions =  aiProcess_GenSmoothNormals;

	const aiScene* scene = importer.ReadFile(MESH_PATH + name, importOptions);
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
			glm::vec2 vec2Data;
			vec2Data.x = mesh->mTextureCoords[0][i].x;
			vec2Data.y = mesh->mTextureCoords[0][i].y;
			vert.uv = vec2Data;
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

	Material* mat = nullptr;
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		mat = loadMaterial(material);
	}
	

	Mesh* l_mesh = new Mesh(vertices, indices);
	l_mesh->addMaterial(mat);
	return l_mesh;
}

Material* MeshLoader::loadMaterial(aiMaterial* material) {

	aiString name;


	material->Get(AI_MATKEY_NAME, name);

	logInfo(name.C_Str());


	if (MaterialMap::getInstance()->existsWithName(name.C_Str())) {
		return MaterialMap::getInstance()->getMaterial(name.C_Str());
	}
	else {
		Material* mat = new Material(); //This could well be the problem
		aiColor3D col;
		material->Get(AI_MATKEY_COLOR_DIFFUSE, col);
		mat->diffuseCol = glm::vec3(col.r, col.g, col.b);

		material->Get(AI_MATKEY_COLOR_AMBIENT, col);
		mat->ambientCol = glm::vec3(col.r, col.g, col.b);

		material->Get(AI_MATKEY_COLOR_SPECULAR, col);
		mat->specCol = glm::vec3(col.r, col.g, col.b);

		mat->name = name.C_Str();
	
		loadTextures(material, aiTextureType::aiTextureType_DIFFUSE, mat);

		MaterialMap::getInstance()->insertMat(name.C_Str(), mat); 
		
		return mat;
	}
}

void MeshLoader::loadTextures(aiMaterial* material, aiTextureType textureType, Material* engineMat)
{	
	for (unsigned int i = 0; i < material->GetTextureCount(textureType); i++) {
		aiString str;
		std::string rString;
		std::string name;
		material->GetTexture(textureType, i, &str); //Get the path for the texture
		
		rString = str.C_Str();
		engineMat->name = rString;
		//std::cout << rString << std::endl;
		name = rString.substr(rString.find_last_of("\\/"), rString.length());

		//Then insert the pair into the material 
		engineMat->textures.push_back(m_textureMap->insert(name, TEXTURE_PATH + rString));
	}
}

