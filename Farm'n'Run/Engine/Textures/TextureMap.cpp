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
	//cleanUp();
}

void TextureMap::destroy() {
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

void TextureMap::insert(const std::string& textureName, const std::string& textureFile, const std::string& type)
{
	//If the texture already exists in the textureMap
	if (textureExists(textureName)) {
		m_textures[textureName].binds++;
		logWarning("Texture already exists");
		return;
	}

	//Create and insert the texture	
	GLuint texture;
	int width, height, nrOfComponents;
	unsigned char* textureData = stbi_load(textureFile.c_str(), &width, &height, &nrOfComponents, 0);
	if (textureData) {
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
			   
		//Set the texture at the position
		m_textures[textureName].textureID = texture;
		m_textures[textureName].binds++;
		m_textures[textureName].type = type;
	}
	else {
		logWarning("Failed to read texture");
	}
	stbi_image_free(textureData);
}
const GLuint& TextureMap::getTextureID(const std::string& name)
{
	if (textureExists(name)) {
		return m_textures[name].textureID;
	}

	return 0;
}

void TextureMap::removeTexture(const std::string& name)
{
	//if the texture doesn't exist
	if (!textureExists(name)) {
		return;
	}
	m_textures[name].binds--;
	//If we deleted the only texture in use
	if (m_textures[name].binds <= 0) {
		//Remove the texture entirely 
		glDeleteTextures(1, &m_textures[name].textureID);
	}
}

void TextureMap::cleanUp()
{
	std::map<std::string, TextureType>::iterator iter;

	for (iter = m_textures.begin(); iter != m_textures.end(); iter++) {
		glDeleteTextures(1, &iter->second.textureID);
	}

	m_textures.clear();
}


bool TextureMap::textureExists(const std::string& name)
{
	if (m_textures.find(name) != m_textures.end()) {
		return true;
	}

	return false;
}
