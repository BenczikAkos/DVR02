#version 330 core
layout (location = 0) out vec2 intersections;

uniform mat4 ViewMatrix;
uniform vec2 WindowSize;
uniform vec3 CameraPos;
uniform vec3 AABBScale;
uniform sampler3D Volume;
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

void main()
{
    vec3 rayDirection;
    rayDirection.xy = 2.0f * gl_FragCoord.xy / WindowSize - 1.0;
    rayDirection.z = 2.0f;
    rayDirection = (vec4(rayDirection, 0) * ViewMatrix).xyz;

    Ray eye = Ray(CameraPos, normalize(rayDirection));
    AABB aabb = AABB(vec3(-1.0f)*AABBScale, vec3(1.0f)*AABBScale);

    float tnear = -1.0f;
    float tfar  = -1.0f;
    bool inside = false;
    if(IntersectBox(eye, aabb, tnear, tfar))
    {
        vec3 rayStart = (eye.Origin + eye.Dir * tnear - aabb.Min) / (aabb.Max - aabb.Min);
        vec3 rayStop = (eye.Origin + eye.Dir * tfar - aabb.Min) / (aabb.Max - aabb.Min);
        vec3 pos = rayStart;
        vec3 step = normalize(rayStop-rayStart) * stepLength;
        float travel = distance(rayStart, rayStop);
        float rayParameter = tnear;
        tnear = -1.0f;
        for (int i=0; travel > 0.0; ++i, pos += step, travel -= stepLength, rayParameter += stepLength)
        {
            float intensity = texture(Volume, pos).r;
            if(intensity > 0.001f && !inside)
            {
                tnear = rayParameter;
                inside = true;
            }
            if(intensity < 0.001f && inside)
            {
                tfar = rayParameter;
                break;
            }
        }
        intersections = vec2(tnear, tfar);
    }
   else
   {
       intersections = vec2(-1.0f);
   }
   //intersections = rayDirection.xy;
}
