#version 150
out highp vec4 fragColor;

uniform vec2 WindowSize;
uniform float stepLength;
uniform float intensityMax;
uniform sampler2D enterTexture;
uniform sampler2D exitTexture;
uniform sampler3D Volume;
uniform sampler2D TransferFunction;

vec3 computeGradient(vec3 pos) {
    vec3 step = vec3(1.0 / 256.0);
    vec3 sample0, sample1;
    sample0.x = texture(Volume, vec3(pos.x - step.x, pos.y, pos.z)).r;
    sample0.y = texture(Volume, vec3(pos.x, pos.y - step.y, pos.z)).r;
    sample0.z = texture(Volume, vec3(pos.x, pos.y, pos.z - step.z)).r;
    sample1.x = texture(Volume, vec3(pos.x + step.x, pos.y, pos.z)).r;
    sample1.y = texture(Volume, vec3(pos.x, pos.y + step.y, pos.z)).r;
    sample1.z = texture(Volume, vec3(pos.x, pos.y, pos.z + step.z)).r;
    return normalize(sample1 - sample0);
}

void main()
{
    vec2 screenPos = gl_FragCoord.xy / WindowSize;
    vec3 enterPoint = texture(enterTexture, screenPos).xyz;
    vec3 exitPoint = texture(exitTexture, screenPos).xyz;
    vec3 travel = exitPoint - enterPoint;
    float travelLength = length(travel);
    vec3 pos = enterPoint;
    vec3 color = vec3(0.0f);
    for(float t = 0.0f; t < travelLength; t += stepLength)
    {
        pos = enterPoint + t * normalize(travel);
        float intensity = texture(Volume, pos).r;
        if(intensity >= intensityMax){
            vec3 gradient = computeGradient(pos);
            gradient = normalize(gradient);
            t += travelLength;
            color = (gradient + 1.0f) / 2.0;
        }
    }
    fragColor = vec4(color, 1.0f);
}

