#version 330 core
// layout (location = 0) out vec3 intersection;
out highp vec4 intersection;

in vec3 modelPos;

void main()
{
    if(modelPos.z < 0.0){
        intersection = vec4(0.8471, 0.4471, 0.4471, 1.0);
        return;
    }
    if(modelPos.z > 1.0){
        intersection = vec4(0.3529, 0.5961, 0.8588, 1.0);
        return;
    }
    intersection = vec4(vec3(modelPos.z), 1.0);
    return;
}
