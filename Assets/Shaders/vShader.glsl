#version 430

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 1) in vec2 uv;

uniform mat4 prjMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

out vec2 f_uv;
out vec3 f_normal;
void main() {
    gl_Position = prjMatrix * viewMatrix * modelMatrix * vec4(position, 1);
    f_uv = uv;
    f_normal = normalize(mat3(transpose(inverse(modelMatrix))) * normal);
}
