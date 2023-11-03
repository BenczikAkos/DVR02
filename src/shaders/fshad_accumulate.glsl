#version 150
out highp vec4 fragColor;

uniform vec2 WindowSize;
uniform float stepLength; 
uniform sampler2D enterTexture;
uniform sampler2D exitTexture;
uniform sampler3D Volume;
uniform sampler2D TransferFunction;

void main()
{   
    vec2 screenPos = gl_FragCoord.xy / WindowSize;
    vec3 enterPoint = texture(enterTexture, screenPos).xyz;
    vec3 exitPoint = texture(exitTexture, screenPos).xyz;
    vec3 travel = exitPoint - enterPoint;
    float travelLength = length(travel);
    vec3 pos = enterPoint;
    vec4 color = vec4(0.0f);
    for(float t = 0.0f; t < travelLength; t += stepLength)
    {
        pos = enterPoint + t * normalize(travel);
        float intensity = texture(Volume, pos).r;
        vec4 transferColor = texture(TransferFunction, vec2(intensity, 0.5f));
        color.rgb += transferColor.rgb * (1 - color.a) * transferColor.a;
        color.a += (1 - color.a) * transferColor.a;
        
    }
    // color.rgb = color.a * color.rgb;
    // color.a = 1.0;
    fragColor = color;
    return;
}