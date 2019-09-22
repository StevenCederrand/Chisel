#ifndef _PCH_h
#define _PCH_h


//Standard includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <limits.h>
#include <time.h>
#include <vector>
#include <map>
#include <unordered_map>
#include <math.h>
#include <chrono>
#include <thread>
#include <string>
#include <stdio.h>

//GL
#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

//Assimp 
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Engine Includes
#include <Engine/Textures/stb_image.h>
#include <Engine/Utility/Input.h>
#include <Engine/Utility/Log.h>
#include <Engine/Rendering/Renderer.h>
//Game Includes
#include <Engine/Shaders/ShaderMap.h>

#define SHADER_PATH "Assets/Shaders/"
#define MESH_PATH "Assets/Mesh/"
#define TEXTURE_PATH "Assets/Textures/"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


#endif 