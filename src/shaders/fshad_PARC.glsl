#version 330 core
layout (location = 0) out vec3 intersection;
// out highp vec3 intersection;

in vec3 modelPos;

void main()
{
    intersection = vec3(modelPos.z);
    return;
}
