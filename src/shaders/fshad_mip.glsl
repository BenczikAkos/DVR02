#version 150
out highp vec4 fragColor;

uniform vec2 WindowSize;    
uniform sampler2D PARC;

void main()
{
    vec2 screenPos = gl_FragCoord.xy / WindowSize;
    vec3 intersections = texture(PARC, screenPos).xyz;
    fragColor = vec4(intersections, 1.0f);
    return;
}
