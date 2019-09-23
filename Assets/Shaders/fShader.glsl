#version 430

vec3 lightDirection = vec3(0.5f, 0.5f, 0);

in vec2 f_uv;
in vec3 f_normal;
in vec4 f_position;


uniform vec3 DiffuseCol;

out vec4 color;

void main() {
    vec3 normal = normalize(f_normal);
    vec3 lightDir = normalize(vec3(f_position.xyz - lightDirection));
    float diff = max(dot(normal, lightDir), 0.0f);


    color = vec4((DiffuseCol * diff), 1);
}
