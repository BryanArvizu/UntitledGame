#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform vec3 lightColor;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = vec4(lightColor, 1.0f);
}