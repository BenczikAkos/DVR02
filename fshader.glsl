#version 150
out highp vec4 fragColor;

uniform mat4 mvMatrix;
uniform mat4 projMatrix;
uniform float FocalLength;
uniform vec2 WindowSize;
uniform vec3 cameraPos;

struct Ray {
    vec3 Origin;
    vec3 Dir;
};

struct AABB {
    vec3 Min;
    vec3 Max;
};

void IntersectBox(Ray r, AABB aabb, out float t0, out float t1)
{
    vec3 invR = 1.0 / r.Dir;
    vec3 tbot = invR * (aabb.Min-r.Origin);
    vec3 ttop = invR * (aabb.Max-r.Origin);
    vec3 t_enter = min(ttop, tbot);
    vec3 t_exit = max(ttop, tbot);
    t0 = max(t_enter.x, max(t_enter.y, t_enter.z));
    t0 = max(0, t0);
    t1 = min(t_exit.x, min(t_exit.y, t_exit.z));
}

void main()
{
   vec3 rayDirection;
   rayDirection.xy = 2.0 * gl_FragCoord.xy / WindowSize - 1.0;
   rayDirection.z = 1.0f;
   rayDirection = (vec4(rayDirection, 0)).xyz;

   Ray eye = Ray( cameraPos, normalize(rayDirection) );
   AABB aabb = AABB(vec3(-1.0), vec3(1.0));

   float tnear, tfar;
   IntersectBox(eye, aabb, tnear, tfar);

   vec3 rayStart = eye.Origin + eye.Dir * tnear;
   vec3 rayStop = eye.Origin + eye.Dir * tfar;

    // Transform from object space to texture coordinate space:
   rayStart = 0.5 * (rayStart + 1.0);
   rayStop = 0.5 * (rayStop + 1.0);
   vec3 outcolor = vec3(0.0f);
   //  // Perform the ray marching:
   vec3 pos = rayStart;
   float stepSize = 0.001f;
   vec3 step = normalize(rayStop-rayStart) * stepSize;
   float travel = distance(rayStop, rayStart);
   for (int i=0; i < 1000 && travel > 0.0; ++i, pos += step, travel -= stepSize)
   {
       outcolor += abs(step);
   }
   fragColor = vec4(outcolor, 1);

}
