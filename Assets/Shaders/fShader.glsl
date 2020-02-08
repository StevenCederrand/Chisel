#version 430
#define MAX_LIGHTS 64

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float ambientStrength;
};

struct Pointlight {
    vec4 colour;
    vec4 position;
    vec3 attenuation;
};

in vec4 f_position; //Inbound fragment data
in vec3 f_normal;   //Inbound fragment data, is already normalized!
in vec2 f_uv;       //Inbound fragment data

uniform sampler2D diffuseTexture;   //Material diffuse texture
uniform vec3 AmbientCol;    //Material ambient colour
uniform vec3 DiffuseCol;    //Material diffuse colour
uniform int Lightcount;     //The number of point lights in the scene
uniform Pointlight Pointlights[MAX_LIGHTS];

uniform DirectionalLight directionalLight;

out vec4 color;

float G_DSTR = 0.5f;
float ambStr = 0.1f;

//Performes point light calculations
vec3 calculatePointlight();
//Performes directional light calculations
vec3 calculateDirlight(vec4 colTex);
vec3 calculateDirlight(vec3 colour);

void main() {
    vec3 col = vec3(0);
    vec4 colTex = texture(diffuseTexture, f_uv);

    if(colTex.a == 0) {
        discard;    //Discard the fragment as early as possible
    }

    col = colTex.rgb * directionalLight.ambientStrength;
    col += calculateDirlight(colTex);
    col += calculateDirlight(DiffuseCol);

    color = vec4(col, 1);
}

vec3 calculateDirlight(vec4 colTex) {

    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(f_normal, lightDir), 0.0f);
    return colTex.rgb * diff * directionalLight.color;
}

vec3 calculateDirlight(vec3 colour){
    vec3 lightDir = normalize(-directionalLight.direction);
    float diff = max(dot(f_normal, lightDir), 0.0f);
    return colour * diff * directionalLight.color;
}


vec3 calculatePointlight() {
    return vec3(0, 0, 0);
}
