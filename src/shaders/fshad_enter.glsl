#version 330 core
out highp vec4 fragColor;

uniform vec2 WindowSize;    
uniform sampler2D enterTexture;
uniform sampler2D exitTexture;

void main()
{
    vec2 screenPos = gl_FragCoord.xy / WindowSize;
    vec3 enterPoint = texture(enterTexture, screenPos).xyz;
    vec3 exitPoint = texture(exitTexture, screenPos).xyz;
    enterPoint -= vec3(0.5f);
    enterPoint *= 10.0f;
    fragColor = vec4(enterPoint, 1.0f);
    return;
}
