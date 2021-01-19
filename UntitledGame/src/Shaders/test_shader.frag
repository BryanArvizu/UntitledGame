#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform float time;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;


void main()
{
    vec3 result = vec3(1.0f, 1.0f, 1.0f) * vec3(texture(texture0,TexCoord));

    FragColor = vec4(result, 1.0f);
}