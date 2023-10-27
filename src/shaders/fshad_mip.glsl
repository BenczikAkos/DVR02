#version 150
out highp vec4 fragColor;

uniform vec2 WindowSize;    
uniform sampler2D PARC;

void main()
{
    vec2 screenPos = gl_FragCoord.xy / WindowSize;
    vec3 intersections = texture(PARC, screenPos).xyz;
    float blueComponent = 0.3f;
    if (length(intersections) > 0.0f){
        blueComponent = 1.0f;
        screenPos = vec2(0.0f);
    }
    fragColor = vec4(screenPos, blueComponent, 1.0f);
    return;
}
