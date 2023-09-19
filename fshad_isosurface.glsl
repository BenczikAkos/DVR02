#version 150
out highp vec4 fragColor;

uniform mat4 ViewMatrix;
uniform vec2 WindowSize;
uniform vec3 CameraPos;
uniform vec3 AABBScale;
uniform sampler3D Volume;
uniform float intensityMin;
uniform float intensityMax;
uniform float stepLength;


struct Ray {
    vec3 Origin;
    vec3 Dir;
};

struct AABB {
    vec3 Min;
    vec3 Max;
};

bool IntersectBox(Ray r, AABB aabb, out float t0, out float t1)
{
    vec3 invR = 1.0 / r.Dir;
    vec3 tbot = invR * (aabb.Min-r.Origin);
    vec3 ttop = invR * (aabb.Max-r.Origin);
    vec3 t_enter = min(ttop, tbot);
    vec3 t_exit = max(ttop, tbot);
    t0 = max(t_enter.x, max(t_enter.y, t_enter.z));
    t0 = max(0, t0);
    t1 = min(t_exit.x, min(t_exit.y, t_exit.z));
    return t1 > t0;
}

float cap(float value, float min, float max) {
    if (value > max || value < min) {
        return 0.0;
    } else {
        return value;
    }
}

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

vec4 color_transfer(float intensity)
{
    vec3 high = vec3(1.0, 1.0, 1.0);
    vec3 low = vec3(0.0, 0.0, 0.0);
    float alpha = (exp(intensity) - 1.0) / (exp(1.0) - 1.0);
    return vec4(intensity * high + (1.0 - intensity) * low, alpha);
}

void main()
{
   vec3 rayDirection;
   rayDirection.xy = 2.0f * gl_FragCoord.xy / WindowSize - 1.0;
   rayDirection.z = 2.0f;
   rayDirection = (vec4(rayDirection, 0) * ViewMatrix).xyz;

   Ray eye = Ray(CameraPos, normalize(rayDirection));
   AABB aabb = AABB(vec3(-1.0f)*AABBScale, vec3(1.0f)*AABBScale);

   float tnear, tfar;
    if(IntersectBox(eye, aabb, tnear, tfar)){
        vec3 rayStart = (eye.Origin + eye.Dir * tnear - aabb.Min) / (aabb.Max - aabb.Min);
        vec3 rayStop = (eye.Origin + eye.Dir * tfar - aabb.Min) / (aabb.Max - aabb.Min);
        // Perform the ray marching:
        vec3 pos = rayStart;
        vec3 step = normalize(rayStop-rayStart) * stepLength;
        float travel = distance(rayStart, rayStop);
        bool stop = false;
        vec3 color = vec3(0.0f);
        while (travel > 0.0f && !stop)
        {
            vec4 data = texture(Volume, pos);
            float intensity = data.r;
            vec3 sample0, sample1;
            // vec3 scaledPosition = pos * 256.0f - vec3(0.5f);
            // vec3 fraction = scaledPosition - floor(scaledPosition);
            // vec3 correctionPolynomial = (fraction * (fraction - vec3(1.0f)) / 2.0f);
            // intensity += dot((sample0 - 2.0f * vec3(intensity) + sample1), correctionPolynomial);
            if(intensity >= intensityMax){
                // vec3 gradient = data.gba;
                // gradient = normalize(gradient);
                vec3 gradient = computeGradient(pos, sample0, sample1);
                vec3 lightDir = normalize(CameraPos - pos);
                vec3 viewDir = normalize(CameraPos - pos);
                vec3 halfwayDir = normalize(lightDir + viewDir);  
                float diff = max(dot(gradient, lightDir), 0.0);
                vec3 diffuse = diff * vec3(1.0) * vec3(0.8667, 0.4902, 0.0588);
                
                float spec = pow(max(dot(gradient, halfwayDir), 0.0), 20.0f);
                vec3 spec_color = spec * vec3(0.3137, 0.2275, 0.6588);
                // color = 0.1f * vec3(1.0) + 0.5f * diffuse + 0.4f * spec_color;
                color = gradient;
                stop = true;
            }
            travel -= stepLength;
            pos += step;
        }
        fragColor = vec4(color, 1.0f);
    }
   else{
       fragColor = vec4(0.0f);
   }
}
