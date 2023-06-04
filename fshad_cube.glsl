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
        float maximum_intensity = 0.0f;
        vec4 color = vec4(0.0f);
        while (travel > 0.0f && color.a < 1.0f)
        {
            float intensity = texture(Volume, pos).r;
            vec4 act_tex = color_transfer(intensity);
            color.rgb = act_tex.a * act_tex.rgb + (1 - act_tex.a) * color.a * color.rgb;
            color.a = act_tex.a + (1 - act_tex.a) * color.a;
            travel -= stepLength;
            pos += step;
        }
        color.rgb = color.a * color.rgb;
        color.a = 1.0;
        // fragColor = vec4(maximum_intensity, maximum_intensity, maximum_intensity, 1.0f);
        fragColor = color;
    }
   else{
       fragColor = vec4(0.0f);
   }
}
