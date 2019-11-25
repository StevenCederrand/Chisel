//Vertex Shader for the skybox
#version 430

layout(location = 0) in vec3 position;

out vec3 textureDir;

/*We don't take in the model matrix, becasue we don't want the skybox in world space */
uniform mat4 prjMatrix;
uniform mat4 viewMatrix;

void main() {
    textureDir = position;
    vec4 pos = prjMatrix * viewMatrix * vec4(position, 1.0f);
    gl_Position = pos.xyww;
}
