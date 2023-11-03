#version 150
out highp vec4 fragColor;

uniform vec2 WindowSize;
uniform float stepLength; 
uniform sampler2D enterTexture;
uniform sampler2D exitTexture;
uniform sampler3D Volume;

void main()
{   
    vec2 screenPos = gl_FragCoord.xy / WindowSize;
    vec3 enterPoint = texture(enterTexture, screenPos).xyz;
    vec3 exitPoint = texture(exitTexture, screenPos).xyz;
    vec3 travel = exitPoint - enterPoint;
    float travelLength = length(travel);
    vec3 pos = enterPoint;
    float maxIntensity = 0.0f;
    for(float t = 0.0f; t < travelLength; t += stepLength)
    {
        pos = enterPoint + t * normalize(travel);
        float intensity = texture(Volume, pos).r;
        if(intensity > maxIntensity)
        {
            maxIntensity = intensity;
        }
    }
    float small = texture(Volume, enterPoint).r;
    fragColor = vec4(maxIntensity, maxIntensity, maxIntensity, 1.0f);
    return;
}
