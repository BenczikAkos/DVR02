#version 150
out highp vec4 fragColor;

uniform vec2 WindowSize;
uniform float stepLength;
uniform vec3 CameraPos;
uniform float intensityMax;
uniform sampler2D enterTexture;
uniform sampler2D exitTexture;
uniform sampler3D Volume;
uniform sampler2D TransferFunction;

vec3 computeGradient(vec3 pos, out vec3 sample0, out vec3 sample1) {
    vec3 step = vec3(1.0 / 256.0);
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
        vec3 sample0, sample1;
        // vec3 scaledPosition = pos * 256.0f - vec3(0.5f);
        // vec3 fraction = scaledPosition - floor(scaledPosition);
        // vec3 correctionPolynomial = (fraction * (fraction - vec3(1.0f)) / 2.0f);
        // intensity += dot((sample0 - 2.0f * vec3(intensity) + sample1), correctionPolynomial);
        if(intensity >= intensityMax){
            // vec3 gradient = data.gba;
            vec3 gradient = computeGradient(pos, sample0, sample1);
            gradient = normalize(gradient);
            // vec3 lightDir = normalize(CameraPos - pos) * -1.0f;
            // vec3 viewDir = normalize(CameraPos - pos);
            // vec3 halfwayDir = normalize(lightDir + viewDir);  
            // float diff = max(dot(gradient, lightDir), 0.0);
            // vec3 diffuse_color = texture(TransferFunction, vec2(intensity, 0.5f)).rgb;
            // vec3 diffuse = diff * vec3(1.0) * diffuse_color;
            
            // float spec = pow(max(dot(gradient, halfwayDir), 0.0), 20.0f);
            // vec3 spec_color = spec * vec3(0.3137, 0.2275, 0.6588);
            // color = 0.1f * vec3(1.0) + 0.5f * diffuse + 0.4f * spec_color;
            t += travelLength;
            color = abs(gradient);
        }
    }
    fragColor = vec4(color, 1.0f);
}

