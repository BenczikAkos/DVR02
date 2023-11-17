#version 150
out highp vec4 fragColor;

uniform vec2 WindowSize;
uniform float stepLength;
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
    return (sample1 - sample0) / 2.0f;
}

mat3 computeHessian(vec3 pos, vec3 sample_1minus, vec3 sample_1plus, float intensity) {
    vec3 step = vec3(1.0 / 256.0);
    vec3 sample_2minus, sample_2plus;
    //sample_2minus.x contains f(x, y-, z-), so the only coordinate that is not reduced is the "index"
    sample_2minus.x = texture(Volume, vec3(pos.x, pos.y - step.y, pos.z - step.z)).r;
    sample_2minus.y = texture(Volume, vec3(pos.x - step.x, pos.y, pos.z - step.z)).r;
    sample_2minus.z = texture(Volume, vec3(pos.x - step.x, pos.y - step.y, pos.z)).r;
    sample_2plus.x = texture(Volume, vec3(pos.x, pos.y + step.y, pos.z + step.z)).r;
    sample_2plus.y = texture(Volume, vec3(pos.x + step.x, pos.y, pos.z + step.z)).r;
    sample_2plus.z = texture(Volume, vec3(pos.x + step.x, pos.y + step.y, pos.z)).r;
    float dfdxdy = (sample_2plus.z - sample_1plus.x - sample_1plus.y + 2.0f * intensity - sample_1minus.x - sample_1minus.y + sample_2minus.z) / (2.0f * step.x *step.y);
    float dfdxdz = (sample_2plus.y - sample_1plus.x - sample_1plus.z + 2.0f * intensity - sample_1minus.x - sample_1minus.z + sample_2minus.y) / (2.0f * step.x *step.z);
    float dfdydz = (sample_2plus.x - sample_1plus.y - sample_1plus.z + 2.0f * intensity - sample_1minus.y - sample_1minus.z + sample_2minus.x) / (2.0f * step.y *step.z);
    float dfdxdx = (sample_1plus.x - 2.0f * intensity + sample_1minus.x) / (step.x * step.x);
    float dfdydy = (sample_1plus.y - 2.0f * intensity + sample_1minus.y) / (step.y * step.y);
    float dfdzdz = (sample_1plus.z - 2.0f * intensity + sample_1minus.z) / (step.z * step.z);
    return mat3(dfdxdx, dfdxdy, dfdxdz, dfdxdy, dfdydy, dfdydz, dfdxdz, dfdydz, dfdzdz);
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
            vec3 sample_1minus, sample_1plus;
            vec3 gradient = computeGradient(pos, sample_1minus, sample_1plus);
            vec3 normal = -normalize(gradient);
            mat3 P = mat3(1.0f) - outerProduct(normal, normal);
            mat3 Hessian = computeHessian(pos, sample_1minus, sample_1plus, intensity);
            mat3 G = -P * Hessian * P;
            G = G * (1.0f / length(gradient));
            float traceG = G[0][0] + G[1][1] + G[2][2];
            mat3 GtimesGTransposed = G * transpose(G);
            float FrobeniusG = sqrt(GtimesGTransposed[0][0] + GtimesGTransposed[1][1] + GtimesGTransposed[2][2]);
            float determinant = sqrt(2.0f * FrobeniusG * FrobeniusG - traceG * traceG);
            float kappa1 = (traceG + determinant) / 2.0f;
            float kappa2 = (traceG - determinant) / 2.0f;
            float mean = (kappa1 + kappa2) / 2.0f;
            t += travelLength;
            color = normalize(vec3(abs(kappa1), abs(kappa2), 0.0f));
        }
    }
    fragColor = vec4(color, 1.0f);
}

