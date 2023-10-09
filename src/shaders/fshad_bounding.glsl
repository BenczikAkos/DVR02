#version 330 core
layout (location = 0) out vec2 intersections;

uniform mat4 ViewMatrix;
uniform vec2 WindowSize;
uniform vec3 CameraPos;
uniform vec3 AABBScale;
uniform sampler3D Volume;
uniform sampler2D TransferFunction;
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
        float maximum_intensity = 0.0f;
        vec4 color = vec4(0.0f);
        for (int i=0; i < 1.0/stepLength && travel > 0.0; ++i, pos += step, travel -= stepLength)
        {
            float intensity = texture(Volume, pos).r;
            intensity = cap(intensity, intensityMin, intensityMax);
            if (intensity > maximum_intensity) {
                maximum_intensity = intensity;
            }
        }
        fragColor = texture(TransferFunction, vec2(maximum_intensity, 0.5f));
    }
   else{
       fragColor = vec4(0.1f);
   }
}
