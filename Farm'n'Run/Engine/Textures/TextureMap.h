#ifndef _TEXTUREMAP_h
#define _TEXTUREMAP_h
#include <PCH/pch.h>
#include "stb_image.h"

struct TextureType {
	GLuint textureID;
	std::string type;
	int binds; //Keeps track of how many materials are currently using the same textureID.
};

class TextureMap {
public:

	TextureMap();
	~TextureMap();
	//Insert a new texture into the map of textures
	void insert(const std::string& textureName, std::string textureFile, const std::string& type);
	
	const GLuint& getTextureID(const std::string& name);
	//Remove a specific texture
	void removeTexture(const std::string& name);
	//Remove all of the textures
	void cleanUp();

private:
	
	bool textureExists(const std::string& name);
	std::map<std::string, TextureType> m_textures;
};


#endif