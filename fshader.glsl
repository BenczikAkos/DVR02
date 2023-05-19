#version 150
out highp vec4 fragColor;

uniform mat4 ViewMatrix;
uniform vec2 WindowSize;
uniform vec3 CameraPos;
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

vec4 colour_transfer(float intensity)
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
   rayDirection.z = 1.0f;
   rayDirection = (vec4(rayDirection, 0) * ViewMatrix).xyz;

   Ray eye = Ray(CameraPos, normalize(rayDirection));
   AABB aabb = AABB(vec3(-1.0f), vec3(1.0f));

   float tnear, tfar;
    if(IntersectBox(eye, aabb, tnear, tfar)){
        vec3 rayStart = (eye.Origin + eye.Dir * tnear - vec3(-1.0f)) / (vec3(1.0f) - vec3(-1.0f));
        vec3 rayStop = (eye.Origin + eye.Dir * tfar - vec3(-1.0f)) / (vec3(1.0f) - vec3(-1.0f));
         // Transform from object space to texture coordinate space:
        // rayStart = 0.5 * (rayStart + 1.0);
        // rayStop = 0.5 * (rayStop + 1.0);
        // Perform the ray marching:
        vec3 pos = rayStart;
        float stepSize = 0.001f;
        vec3 step = normalize(rayStop-rayStart) * stepSize;
        float travel = distance(rayStop, rayStart);
        float maximum_intensity = 0.0f;
        vec4 colour = vec4(0.0f);
        for (int i=0; i < 1000 && travel > 0.0; ++i, pos += step, travel -= stepSize)
        {
             float intensity = texture(Volume, pos).r;

             if (intensity > maximum_intensity) {
                 maximum_intensity = intensity;
             }
            // float intensity = texture(Volume, pos).r;
            // vec4 act_tex = colour_transfer(intensity);
            // colour.rgb = act_tex.a * act_tex.rgb + (1 - act_tex.a) * colour.a * colour.rgb;
            // colour.a = act_tex.a + (1 - act_tex.a) * colour.a;
        }
        fragColor = vec4(maximum_intensity, maximum_intensity, maximum_intensity, 1.0f);
        // fragColor = colour;
    }
   else{
       fragColor = vec4(0.0f);
   }
}
