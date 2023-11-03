#version 420 core
out highp vec4 fragColor;

uniform vec2 WindowSize;    
uniform sampler2D enterTexture;
uniform sampler2D exitTexture;
uniform sampler3D Volume;
// uniform vec3 AABBScale;
// uniform float intensityMin;
// uniform float intensityMax;
uniform float stepLength;

void main()
{
    vec2 screenPos = gl_FragCoord.xy / WindowSize;
    vec3 enterPoint = texture(enterTexture, screenPos).xyz;
    vec3 exitPoint = texture(exitTexture, screenPos).xyz;
    vec3 travelVector = exitPoint - enterPoint;
    vec3 step = normalize(travelVector) * stepLength;
    float travelLength = length(travelVector);
    float maximum_intensity = 0.0f;
    if(travelLength > 0.0f)
    {
        float intensity = texture(Volume, vec3(0.5f)).r;
        vec3 travelColor = vec3(clamp(travelLength, 0.0f, 1.0f));
        fragColor = vec4(travelColor, 1.0f);
    //     for (vec3 pos = enterPoint; travelLength > 0.0f; pos += step, travelLength -= stepLength)
    //     {
    //         float intensity = texture(Volume, pos).r;
    //         if (intensity > maximum_intensity) {
    //             maximum_intensity = intensity;
    //         }
    //     }
    //     fragColor = vec4(vec3(clamp(maximum_intensity, 0.0f, 1.0f)), 1.0f);
    }
    else
    {
        float randomIntensity = 0.0f;
        // float randomIntensity = texture(Volume, vec3(screenPos.x, screenPos.y, 0.5f)).r;
        fragColor = vec4(vec3(randomIntensity), 1.0f);
    }
    // return;
}
