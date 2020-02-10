#version 430
#define MAX_LIGHTS 64

in vec4 f_position; //Inbound fragment data
in vec3 f_normal;   //Inbound fragment data, is already normalized!
in vec2 f_uv;       //Inbound fragment data

out vec4 color;     //Outgoing fragment data

void main() {
    vec3 col = vec3(0, 1000, 0);
    color = vec4(col, 1);
}
