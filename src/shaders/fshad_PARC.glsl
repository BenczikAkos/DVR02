#version 330 core
layout (location = 0) out vec2 intersections;

uniform mat4 ViewMatrix;
uniform vec2 WindowSize;
uniform vec3 CameraPos;
uniform vec3 AABBScale;
uniform sampler3D Volume;

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

   float tnear, tfar;
    if(IntersectBox(eye, aabb, tnear, tfar))
    {
        intersections = vec2(0.7f, 0.0f);
    }
   else
   {
       intersections = vec2(0.2f, 0.0f);
   }
   intersections = CameraPos.xy;
}
