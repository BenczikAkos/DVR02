attribute highp vec4 posAttr;

uniform mat4 ViewMatrix;

out highp vec3 modelPos;

void main() {
   mat4 translateMtx = mat4(1.0, 0.0, 0.0, 0.0,
                            0.0, 1.0, 0.0, 0.0,
                            0.0, 0.0, 1.0, 0.0,
                            -0.5, -0.5, -0.5, 1.0);
   mat4 scaleMtx = mat4(2.0, 0.0, 0.0, 0.0,
                        0.0, 2.0, 0.0, 0.0,
                        0.0, 0.0, 2.0, 0.0,
                        0.0, 0.0, 0.0, 1.0);
   vec4 translated = translateMtx * posAttr;
   vec4 rotated = ViewMatrix * translated;
   modelPos = (posAttr).xyz;
   // gl_Position = scaleMtx * rotated;
   gl_Position = ViewMatrix * posAttr;
}
