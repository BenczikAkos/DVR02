attribute highp vec4 posAttr;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main() {
   gl_Position = ProjectionMatrix * ViewMatrix * posAttr;
}
