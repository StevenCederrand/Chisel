#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 1) in vec2 uv;

uniform mat4 prjMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 f_uv;
out vec3 f_normal;
out vec4 f_position;
void main() {
    f_position = modelMatrix * vec4(position, 1);
    gl_Position = prjMatrix * viewMatrix * f_position;
    f_uv = uv;
    f_normal = mat3(transpose(inverse(modelMatrix))) * normal;
}
