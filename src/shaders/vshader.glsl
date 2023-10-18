attribute highp vec4 posAttr;

uniform mat4 ViewMatrix;

void main() {
   gl_Position = posAttr * ViewMatrix;
}
