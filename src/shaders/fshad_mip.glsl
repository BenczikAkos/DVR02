#version 150
out highp vec4 fragColor;

uniform mat4 ViewMatrix;
uniform vec2 WindowSize;
uniform vec3 CameraPos;
uniform vec3 AABBScale;

uniform sampler3D Volume;
uniform sampler2D TransferFunction;
uniform sampler2D PARC;
uniform float intensityMin;
uniform float intensityMax;
uniform float stepLength;


void main()
{
    vec3 intersections = texture(PARC, vec2(gl_FragCoord.xy / WindowSize)).xyz;
    fragColor = vec4(intersections, 1.0f);
    return;
}
