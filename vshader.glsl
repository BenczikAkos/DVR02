#version 150

in vec4 vertex;
in vec3 normal;

uniform mat4 projMatrix;
uniform mat4 mvMatrix;

void main() {
    mat4 mine;
    mine[0] = vec4(1.6f, 0.0f, 0.0f, 0.0f);
    mine[1] = vec4(0.0f, -2.42f, 0.0f, 0.0f);
    mine[2] = vec4(0.0f, 0.0f, 1.0f, 0.0f);
    mine[3] = vec4(0.0f, 0.0f, 1.5f, 1.5f);
   gl_Position = projMatrix * mvMatrix * vertex;
   //gl_Position = mine * vertex;
}
