#version 330 core

out vec4 FragColor;

uniform float time;

void main()
{
    //vec3 result = vec3((cos(time*1)*0.5)+0.5, (cos(time*2)*0.5)+0.5, (cos(time*3)*0.5)+0.5);
    vec3 result = vec3(1.0f, 0.0f, 1.0f);

    FragColor = vec4(result, 1.0f);
}