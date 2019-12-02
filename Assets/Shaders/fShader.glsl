#version 430

vec3 lightDirection = vec3(-20, -20.0, 50);

in vec4 f_position;
in vec3 f_normal;
in vec2 f_uv;

uniform sampler2D diffuseTexture;
uniform vec3 AmbientCol;
uniform vec3 DiffuseCol;

out vec4 color;

float G_DSTR = 0.5f;
float ambStr = 0.1f;

void main() {
    vec3 col = vec3(0);
    vec3 colTex = texture(diffuseTexture, f_uv).rgb;

    vec3 normal = normalize(f_normal);
    vec3 lightDir = normalize(vec3(f_position.xyz - lightDirection));
    float diff = max(dot(normal, lightDir), 0.0f);

    col = (DiffuseCol * diff) + colTex * diff;
    color = vec4(col, 1);
}
