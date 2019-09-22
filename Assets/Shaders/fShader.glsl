#version 430

in vec2 f_uv;
in vec3 f_normal;
uniform vec3 DiffuseCol;

out vec4 color;

void main() {
    color = vec4(DiffuseCol, 1);
}
