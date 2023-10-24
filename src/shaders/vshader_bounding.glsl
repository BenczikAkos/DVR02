attribute highp vec4 posAttr;

uniform mat4 ViewMatrix;

void main() {
   mat4 translateMtx = mat4(1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            -0.5, -0.5, -0.5, 1.0);
   mat4 backtranslateMtx = mat4(1.0, 0.0, 0.0, 0.0,
                              0.0, 1.0, 0.0, 0.0,
                              0.0, 0.0, 1.0, 0.0,
                              0.5, 0.5, 0.5, 1.0);
   vec4 translated = translateMtx * posAttr;
   vec4 rotated = ViewMatrix * translated;
   gl_Position = backtranslateMtx * rotated;
}
