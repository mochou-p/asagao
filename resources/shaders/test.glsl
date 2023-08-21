// asagao/resources/shaders/test.glsl


#stage vertex
#version 460 core

layout (location = 0) in vec4 position;

void main()
{
    gl_Position = position;
}
#endstage

#stage fragment
#version 460 core

out vec4 FragColor;

uniform vec4 u_color;

void main()
{
    FragColor = u_color;
}
#endstage
