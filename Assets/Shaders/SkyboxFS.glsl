//Fragment Shader for the skybox
#version 430

out vec4 skyboxCol;

in vec3 textureDir;

uniform samplerCube cubeMap; //Sampled cubemap texture


void main() {
    //Sample the texture coordinate from the skybox
    skyboxCol = texture(cubeMap, textureDir);
}
