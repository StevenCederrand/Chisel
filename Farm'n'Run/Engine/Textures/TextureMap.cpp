#include "PCH/pch.h"
#include "TextureMap.h"
#define STB_IMAGE_IMPLEMENTATION

TextureMap* TextureMap::m_textureMap;

TextureMap::TextureMap()
{
}

//I will need to figure this out
TextureMap::~TextureMap()
{

}

void TextureMap::destroy() {
	removeAll();
	m_textures.clear();
	delete m_textureMap;
}

TextureMap* TextureMap::getInstance()
{
	if (m_textureMap == nullptr)
	{
		m_textureMap = new TextureMap();
	}
	return m_textureMap;
}
//Returns the textureID
GLuint TextureMap::insert(const std::string& textureName, const std::string& textureFile)
{
	//We take in our texture name, and its filepath
	long long textureHash = hash(textureName);
	
	if (m_textures.find(textureHash) != m_textures.end()) {	//If the texture does exist
		m_textures[textureHash].refCount += 1;		
		return m_textures[textureHash].textureID;
	}
	else {
		/* CREATE THE TEXTURE */
		GLuint texture;
		int width, height, nrOfComponents;
		unsigned char* textureData = stbi_load(textureFile.c_str(), &width, &height, &nrOfComponents, 0);

		if (textureData) {
			Texture tex;
			tex.refCount = 1;
			tex.textureHash = textureHash;

			GLenum textureFormat;
			if (nrOfComponents == 1) {
				textureFormat = GL_RED;
			}
			else if (nrOfComponents == 3) {
				textureFormat = GL_RGB;
			}
			else if (nrOfComponents == 4) {
				textureFormat = GL_RGBA;
			}
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			tex.textureID = texture;

			//Assign the texture
			m_textures[textureHash] = tex;
			stbi_image_free(textureData);
			return tex.textureID;
		}
		else {
			logWarning("Failed to read texture");
			stbi_image_free(textureData);
			return -1;
		}
		stbi_image_free(textureData);
	}
	return -1;
}

long long TextureMap::hash(const std::string& title)
{
	const int p = 31;
	const int m = 1e9 + 9;
	long long hashValue = 0;
	long long p_pow = 1;

	for (char c : title) {
		hashValue = (hashValue + (c - 'a' + 1) * p_pow) % m;
		p_pow = (p_pow * p) % m;
	}

	return hashValue;
}

const GLuint& TextureMap::getTextureID(const std::string& name)
{
	/*
	if (textureExists(name)) {
		return m_textures[name].textureID;
	}*/

	return 0;
}

void TextureMap::removeTexture(const long long& hash)
{
	if (m_textures.find(hash) != m_textures.end()) { //If the texture does exist
		m_textures[hash].refCount--; //Remove a ref
		
		//Delete the texture
		if (m_textures[hash].refCount <= 0) {
			glDeleteTextures(1, &m_textures[hash].textureID);
			m_textures.erase(hash);
		}
	}
}

void TextureMap::removeAll() {
	std::map<long long, Texture>::iterator it;
	for (it = m_textures.begin(); it != m_textures.end(); it++)
	{
		glDeleteTextures(1, &it->second.textureID);
	}
}

void TextureMap::dump()
{
	std::map<long long, Texture>::iterator it;
	for (it = m_textures.begin(); it != m_textures.end(); it++)
	{
		std::cout << it->second.textureID << " " << it->second.refCount << " " << it->second.textureHash << " \n";
	}
}
